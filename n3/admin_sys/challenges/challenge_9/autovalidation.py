#!/usr/bin/env python3

import os

substring = "facile quand on sait se servir du manuel !"

filepath = './sandbox/le_proverbe_du_jour.txt'

try:
    with open(filepath) as f:
        if substring in f.read():
            print('Félicitations !')
        else:
            print('Essaie encore !')
except Exception:
    print('Essaie encore !')

