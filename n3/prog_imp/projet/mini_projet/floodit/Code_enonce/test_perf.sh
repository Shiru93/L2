#!/bin/bash

# Nom du fichier de sortie
OUTPUT="resultats.csv"

# 1. On initialise le CSV (Ajout de la colonne Max_Bordure_Zone)
echo "Dim;Temps_Naif;Temps_Rapide;Max_Bordure;Max_Bordure_Zone" > $OUTPUT

# 2. On prépare l'affichage dans le terminal (5 colonnes maintenant)
echo "Lancement des tests..."
printf "%-5s | %-15s | %-15s | %-15s | %-15s\n" "Dim" "T. Naif (s)" "T. Rapide (s)" "Max Bordure (s)" "Max Zone (s)"
printf -- "------+-----------------+-----------------+-----------------+-----------------\n"

# On boucle sur les dimensions
for dim in {10..100..10}
do
    # Exo 1 (Naïf)
    t1=$(./Flood-It $dim 4 50 1 1 0 | tail -n 1)
    
    # Exo 2 (Rapide)
    t2=$(./Flood-It $dim 4 50 1 2 0 | tail -n 1)
    
    # Exo 3 (Max Bordure)
    t3=$(./Flood-It $dim 4 50 1 3 0 | tail -n 1)

    # Exo 4 (Max Bordure Zone) - NOUVEAU
    t4=$(./Flood-It $dim 4 50 1 4 0 | tail -n 1)

    # 3. Écriture dans le CSV
    echo "$dim;$t1;$t2;$t3;$t4" >> $OUTPUT

    # 4. Affichage joli dans le terminal
    printf "%-5d | %-15s | %-15s | %-15s | %-15s\n" "$dim" "$t1" "$t2" "$t3" "$t4"
done

echo ""
echo "Terminé ! Fichier généré : $OUTPUT"