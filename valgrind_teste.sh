#!/bin/bash

EXEC="./my_octave"
LOG_FILE="valgrind_log.txt"

echo "Începere verificare teste cu Valgrind..."
echo "----------------------------------------"

# Caută automat toate fișierele .in din orice subfolder și le sortează
for test_in in $(find . -name "*.in" | sort); do
    
    # EXTRAGE NUMELE (Dacă ai iar eroarea de sintaxă aici, șterge linia și scrie-o de mână)
    test_name=$(basename "$test_in" .in)
    
    # Rulează Valgrind
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --error-exitcode=1 \
             --quiet \
             "$EXEC" < "$test_in" > /dev/null 2> "$LOG_FILE"
             
    # Verifică rezultatul
    if [ $? -eq 0 ]; then
        echo -e "[\033[32mOK\033[0m] $test_name (Fără memory leaks)"
    else
        echo -e "[\033[31mFAIL\033[0m] $test_name (Scurgeri detectate):"
        cat "$LOG_FILE"
        echo "----------------------------------------"
    fi
done

rm -f "$LOG_FILE"