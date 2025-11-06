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
  printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
  printf "Command: timeout 3s %s %s\n" "$CUB" "$map" >> "$RESULTS"
  timeout 3s "$CUB" "$map" >> "$RESULTS" 2>&1
  rc=$?
  if [ $rc -eq 0 ]; then
    printf "[OK exit code: 0]\n" >> "$RESULTS"
  else
    if [ $rc -eq 124 ]; then
      printf "[TIMEOUT dopo 3s]\n" >> "$RESULTS"
    else
      printf "[ERROR exit code: %d]\n" "$rc" >> "$RESULTS"
    fi
    failures=$((failures+1))
  fi
  printf "\n" >> "$RESULTS"
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== GOOD MAPS Test run finished: %s ===\n" "$(date)" >> "$RESULTS"
printf "Failures: %d\n" "$failures" >> "$RESULTS"

if [ $failures -ne 0 ]; then
  exit 1
fi

exit 0
