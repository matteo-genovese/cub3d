#!/usr/bin/env bash
# Esegue ./cub3d per ogni file in ./maps/good, salva output in "results"
# Se il processo non termina subito viene ucciso dopo 3 secondi (timeout).
# Considera fallimento qualsiasi exit code != 0 (incluso segfault/timeout).

RESULTS="results"
MAP_DIR="./maps/good"
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

printf "\n=== GOOD MAPS Test run started: %s ===\n\n" "$(date)" >> "$RESULTS"

failures=0

while IFS= read -r -d '' map; do
  # cattura output in variabile temporanea
  output=$(timeout 3s "$CUB" "$map" 2>&1)
  rc=$?
  # Per good maps, exit code 124 (timeout) è OK (finestra aperta)
  # Exit code 0 potrebbe essere OK se il programma termina normalmente
  # Qualsiasi altro exit code è un errore
  printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
  printf "Command: timeout 3s %s %s\n" "$CUB" "$map" >> "$RESULTS"
  echo "$output" >> "$RESULTS"
  if [ $rc -eq 124 ] || [ $rc -eq 0 ]; then
    printf "[OK: exit code %d]\n" "$rc" >> "$RESULTS"
	printf "\n" >> "$RESULTS"
  else
    # Errore - registra nel file results
    printf "[ERRORE: exit code %d]\n" "$rc" >> "$RESULTS"
    printf "\n" >> "$RESULTS"
    failures=$((failures+1))
  fi
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== GOOD MAPS Test run finished: %s ===\n" "$(date)" >> "$RESULTS"

# Count OK results and total maps
ok_count=$(grep -c "\[OK:" "$RESULTS")
total_maps=$(ls -l "$MAP_DIR" | grep -c "^-")

printf "\n=== FINAL SUMMARY ===\n" >> "$RESULTS"
printf "Maps tested: %d\n" "$total_maps" >> "$RESULTS"
printf "Maps passed (OK): %d\n" "$ok_count" >> "$RESULTS"
printf "Failures: %d\n" "$failures" >> "$RESULTS"

if [ "$ok_count" -eq "$total_maps" ]; then
  printf "\n✅ TEST SUCCESSFUL: All %d maps passed!\n" "$total_maps" >> "$RESULTS"
  echo "✅ TEST SUCCESSFUL: All $total_maps maps passed!"
  exit 0
else
  printf "\n❌ TEST FAILED: %d/%d maps failed\n" "$failures" "$total_maps" >> "$RESULTS"
  echo "❌ TEST FAILED: $failures/$total_maps maps failed"
  exit 1
fi
