#!/usr/bin/env python3

import os, subprocess

env=dict(os.environ, LANG="C")

tree = 'sandbox\n├── a\n│\xa0\xa0 ├── a\n│\xa0\xa0 ├── e\n│\xa0\xa0 ├── r\n│\xa0\xa0 ├── t\n│\xa0\xa0 ├── y\n│\xa0\xa0 └── z\n├── e\n└── z\n    ├── r\n    ├── t\n    └── y\n\n6 directories, 6 files\n'
treenew = 'sandbox\n├── a\n│\xa0\xa0 ├── a\n│\xa0\xa0 ├── e\n│\xa0\xa0 ├── r\n│\xa0\xa0 ├── t\n│\xa0\xa0 ├── y\n│\xa0\xa0 └── z\n├── e\n└── z\n    ├── r\n    ├── t\n    └── y\n\n7 directories, 6 files\n'

try:
    if (subprocess.check_output(['tree', 'sandbox']).decode() == tree or
        subprocess.check_output(['tree', 'sandbox']).decode() == treenew):
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

