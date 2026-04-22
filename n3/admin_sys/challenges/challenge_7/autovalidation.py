#!/usr/bin/env python3

import os, subprocess

env=dict(os.environ, LANG="C")

filepath = "./sandbox/0autocompletion/1 ûä_w68ïâ/2N<E0êq-ä0 Xe1/$¹~###~¹/3HB_Lî\\të9î²µ/4 oui c'est par là/{#2¹¬·.·¬¹~+)°$/SOS...---.../FICHIER_VIDE_1"

if os.path.isfile(filepath):
    print('Félicitations !')
else:
    print('Essaie encore !')

