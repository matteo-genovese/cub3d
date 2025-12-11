#!/usr/bin/env bash
# Controlla memory leak con valgrind per ogni file in ./maps/good
# Le good maps aprono una finestra, quindi usiamo timeout breve

RESULTS="results_leaks_good"
MAP_DIR="./maps/good"
CUB="./cub3D"
TIMEOUT=2  # secondi prima di killare il processo

# Remove old results file and create fresh one
rm -f "$RESULTS"
touch "$RESULTS"

if [ ! -x "$CUB" ]; then
  echo "Errore: $CUB non eseguibile o non trovato" >> "$RESULTS"
  exit 1
fi

if [ ! -d "$MAP_DIR" ]; then
  echo "Errore: directory $MAP_DIR non trovata" >> "$RESULTS"
  exit 1
fi

if ! command -v valgrind &> /dev/null; then
  echo "Errore: valgrind non installato" >> "$RESULTS"
  exit 1
fi

printf "=== GOOD MAPS Leak Check started: %s ===\n\n" "$(date)" >> "$RESULTS"

# itera in modo sicuro su tutti i file nella directory (ordinati)
while IFS= read -r -d '' map; do
  printf "Testing: %s\n" "$map"
  
  # esegue valgrind con timeout e cattura output
  output=$(timeout ${TIMEOUT}s valgrind --leak-check=full --show-leak-kinds=all \
    --track-origins=yes --error-exitcode=42 "$CUB" "$map" 2>&1)
  rc=$?
  
  # estrae il summary dei leak
  leak_summary=$(echo "$output" | grep -A 20 "LEAK SUMMARY")
  definitely_lost=$(echo "$output" | grep "definitely lost:" | head -1)
  still_reachable=$(echo "$output" | grep "still reachable:" | head -1)
  all_freed=$(echo "$output" | grep "All heap blocks were freed")
  
  # controlla se ci sono leak (ignoriamo still reachable da MLX)
  has_leaks=0
  if [ -n "$definitely_lost" ]; then
    # se trova "definitely lost", controlla se è > 0
    if echo "$definitely_lost" | grep -qv "0 bytes in 0 blocks"; then
      has_leaks=1
    fi
  elif [ -z "$all_freed" ] && [ -z "$still_reachable" ]; then
    # se non trova né "definitely lost" né "All heap blocks were freed", potrebbe esserci un problema
    # (per good maps, still reachable da MLX è normale)
    has_leaks=1
  fi
  
  # registra sempre (per vedere anche le mappe senza leak)
  printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
  printf "Exit code: %d (124=timeout normale per good maps)\n" "$rc" >> "$RESULTS"
  
  if [ $has_leaks -eq 1 ]; then
    printf "\n%s\n" "$definitely_lost" >> "$RESULTS"
    printf "%s\n" "$still_reachable" >> "$RESULTS"
    echo "$leak_summary" >> "$RESULTS"
    printf "[MEMORY LEAK RILEVATO!]\n" >> "$RESULTS"
  else
    if [ -n "$all_freed" ]; then
      printf "[OK - All heap blocks were freed]\n" >> "$RESULTS"
    elif [ -n "$definitely_lost" ]; then
      printf "%s\n" "$definitely_lost" >> "$RESULTS"
      printf "[OK - Nessun leak]\n" >> "$RESULTS"
    else
      printf "[OK - Nessun leak rilevato]\n" >> "$RESULTS"
    fi
  fi
  printf "\n" >> "$RESULTS"
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== GOOD MAPS Leak Check finished: %s ===\n" "$(date)" >> "$RESULTS"

# Count OK results and total maps
ok_count=$(grep -c "\[OK" "$RESULTS")
total_maps=$(ls -l "$MAP_DIR" | grep -c "^-")

printf "\n=== FINAL SUMMARY ===\n" >> "$RESULTS"
printf "Maps tested: %d\n" "$total_maps" >> "$RESULTS"
printf "Maps passed (OK): %d\n" "$ok_count" >> "$RESULTS"

if [ "$ok_count" -eq "$total_maps" ]; then
  printf "\n✅ TEST SUCCESSFUL: All %d maps passed without leaks!\n" "$total_maps" >> "$RESULTS"
  echo "✅ TEST SUCCESSFUL: All $total_maps maps passed without leaks!"
else
  printf "\n❌ TEST FAILED: %d/%d maps have leaks\n" "$((total_maps - ok_count))" "$total_maps" >> "$RESULTS"
  echo "❌ TEST FAILED: $((total_maps - ok_count))/$total_maps maps have leaks"
fi

