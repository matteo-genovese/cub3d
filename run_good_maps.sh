#!/usr/bin/env bash
# Esegue ./cub3d per ogni file in ./maps/good, salva output in "results"
# Se il processo non termina subito viene ucciso dopo 3 secondi (timeout).
# Considera fallimento qualsiasi exit code != 0 (incluso segfault/timeout).

RESULTS="results"
MAP_DIR="./maps/good"
CUB="./cub3D"

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
  if [ $rc -eq 124 ] || [ $rc -eq 0 ]; then
    : # OK - non registra nulla
  else
    # Errore - registra nel file results
    printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
    printf "Command: timeout 3s %s %s\n" "$CUB" "$map" >> "$RESULTS"
    echo "$output" >> "$RESULTS"
    printf "[ERRORE: exit code %d]\n" "$rc" >> "$RESULTS"
    printf "\n" >> "$RESULTS"
    failures=$((failures+1))
  fi
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== GOOD MAPS Test run finished: %s ===\n" "$(date)" >> "$RESULTS"
printf "Failures: %d\n" "$failures" >> "$RESULTS"

if [ $failures -ne 0 ]; then
  exit 1
fi

exit 0
