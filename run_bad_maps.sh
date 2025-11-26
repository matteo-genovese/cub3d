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
  
  if [ $rc -ne 1 ]; then
    printf "=== MAP: %s ===\n" "$map" >> "$RESULTS"
    printf "Command: timeout 3s %s %s\n" "$CUB" "$map" >> "$RESULTS"
    echo "$output" >> "$RESULTS"
    
    if [ $rc -eq 0 ]; then
      printf "[ERRORE CRITICO: bad map accettata! Exit code: 0]\n" >> "$RESULTS"
    elif [ $rc -eq 124 ]; then
      printf "[ERRORE CRITICO: timeout - finestra grafica aperta! Exit code: 124]\n" >> "$RESULTS"
    else
      printf "[ERRORE: comportamento anomalo. Exit code: %d]\n" "$rc" >> "$RESULTS"
    fi
    printf "\n" >> "$RESULTS"
  fi
done < <(find "$MAP_DIR" -type f -print0 | sort -z)

printf "=== BAD MAPS Test run finished: %s ===\n" "$(date)" >> "$RESULTS"
