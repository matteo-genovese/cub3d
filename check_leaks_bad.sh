#!/usr/bin/env bash
# Controlla memory leak con valgrind per ogni file in ./maps/bad
# Le bad maps dovrebbero terminare con errore SENZA leak

RESULTS="results_leaks_bad"
MAP_DIR="./maps/bad"
CUB="./cub3D"

: > "$RESULTS"  # tronca/crea file results

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

printf "=== BAD MAPS Leak Check started: %s ===\n\n" "$(date)" >> "$RESULTS"

# itera in modo sicuro su tutti i file nella directory (ordinati)
while IFS= read -r -d '' map; do
  printf "Testing: %s\n" "$map"
  
  # esegue valgrind e cattura output
  output=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
    --error-exitcode=42 "$CUB" "$map" 2>&1)
  rc=$?
  
  # estrae il summary dei leak
  leak_summary=$(echo "$output" | grep -A 20 "LEAK SUMMARY")
  definitely_lost=$(echo "$output" | grep "definitely lost:" | head -1)
  all_freed=$(echo "$output" | grep "All heap blocks were freed")
  
  # controlla se ci sono leak
  has_leaks=0
  if [ -n "$definitely_lost" ]; then
    # se trova "definitely lost", controlla se è > 0
    if echo "$definitely_lost" | grep -qv "0 bytes in 0 blocks"; then
      has_leaks=1
    fi
  elif [ -z "$all_freed" ]; then
    # se non trova né "definitely lost" né "All heap blocks were freed", potrebbe esserci un problema
    has_leaks=1
  fi 
  
  # registra solo se ci sono leak
  if [ $has_leaks -eq 1 ]; then
    printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
    printf "Exit code: %d\n" "$rc" >> "$RESULTS"
    printf "\n%s\n" "$definitely_lost" >> "$RESULTS"
    echo "$leak_summary" >> "$RESULTS"
    printf "[MEMORY LEAK RILEVATO!]\n" >> "$RESULTS"
    printf "\n" >> "$RESULTS"
  else
    echo "No memory leaks detected for $map" >> "$RESULTS"
  fi
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== BAD MAPS Leak Check finished: %s ===\n" "$(date)" >> "$RESULTS"

