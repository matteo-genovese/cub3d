#!/usr/bin/env bash
# Esegue ./cub3d per ogni file in ./maps/bad, salva output in "results"
# Se il processo non termina subito viene ucciso dopo 3 secondi (timeout).

RESULTS="results"
MAP_DIR="./maps/bad"
CUB="./cub3D"

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

printf "=== BAD MAPS Test run started: %s ===\n\n" "$(date)" >> "$RESULTS"

# itera in modo sicuro su tutti i file nella directory (ordinati)
while IFS= read -r -d '' map; do
  # cattura output in variabile temporanea
  output=$(timeout 3s "$CUB" "$map" 2>&1)
  rc=$?
  
  # Per le bad maps, ci aspettiamo exit code 1 (errore)
  # Qualsiasi altro exit code indica un problema:
  # - rc=0: mappa accettata (MALE!)
  # - rc=124: timeout raggiunto, finestra aperta (MALE!)
  # - altri: crash o comportamento anomalo
  
  printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
  printf "Command: timeout 3s %s %s\n" "$CUB" "$map" >> "$RESULTS"
  echo "$output" >> "$RESULTS"
  
  if [ $rc -eq 0 ]; then
    printf "[ERRORE CRITICO: bad map accettata! Exit code: 0]\n" >> "$RESULTS"
  elif [ $rc -eq 1 ]; then
    printf "[OK: bad map correttamente rifiutata. Exit code: 1]\n" >> "$RESULTS"
  elif [ $rc -eq 124 ]; then
    printf "[ERRORE CRITICO: timeout - finestra grafica aperta! Exit code: 124]\n" >> "$RESULTS"
  else
    printf "[ERRORE: comportamento anomalo. Exit code: %d]\n" "$rc" >> "$RESULTS"
  fi
  printf "\n" >> "$RESULTS"
  
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== BAD MAPS Test run finished: %s ===\n" "$(date)" >> "$RESULTS"

# Count OK results and total maps
ok_count=$(grep -c "\[OK:" "$RESULTS")
total_maps=$(ls -l "$MAP_DIR" | grep -c "^-")

printf "\n=== FINAL SUMMARY ===\n" >> "$RESULTS"
printf "Maps tested: %d\n" "$total_maps" >> "$RESULTS"
printf "Maps passed (OK): %d\n" "$ok_count" >> "$RESULTS"
printf "Maps failed: %d\n" "$((total_maps - ok_count))" >> "$RESULTS"

if [ "$ok_count" -eq "$total_maps" ]; then
  printf "\n✅ TEST SUCCESSFUL: All %d bad maps correctly rejected!\n" "$total_maps" >> "$RESULTS"
  echo "✅ TEST SUCCESSFUL: All $total_maps bad maps correctly rejected!"
  exit 0
else
  printf "\n❌ TEST FAILED: %d/%d bad maps were incorrectly accepted\n" "$((total_maps - ok_count))" "$total_maps" >> "$RESULTS"
  echo "❌ TEST FAILED: $((total_maps - ok_count))/$total_maps bad maps were incorrectly accepted"
  exit 1
fi
