#!/usr/bin/env bash
# Esegue ./cub3d per ogni file in ./maps/bad, salva output in "results"
# Se il processo non termina subito viene ucciso dopo 3 secondi (timeout).

RESULTS="results"
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

printf "=== Test run started: %s ===\n\n" "$(date)" >> "$RESULTS"

# itera in modo sicuro su tutti i file nella directory (ordinati)
while IFS= read -r -d '' map; do
  printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
  printf "Command: timeout 3s %s %s\n" "$CUB" "$map" >> "$RESULTS"
  # esegue con timeout di 3 secondi, cattura stdout+stderr
  timeout 3s "$CUB" "$map" >> "$RESULTS" 2>&1
  rc=$?
  if [ $rc -eq 124 ]; then
    printf "[TIMEOUT dopo 3s]\n" >> "$RESULTS"
  else
    printf "[exit code: %d]\n" "$rc" >> "$RESULTS"
  fi
  printf "\n" >> "$RESULTS"
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== Test run finished: %s ===\n" "$(date)" >> "$RESULTS"
