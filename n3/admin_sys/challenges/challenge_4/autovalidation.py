#!/usr/bin/env python3

import os, subprocess

env=dict(os.environ, LANG='C', LC_ALL='C')

tree = 'sandbox\n|-- Q\n|   `-- S\n|       `-- D\n|           `-- F\n|               `-- G\n|                   `-- H\n|                       `-- J\n|                           `-- K\n|                               `-- L\n|                                   `-- M\n|-- a\n|-- e\n|-- i\n|-- o\n|-- p\n|-- r\n|-- t\n|-- u\n|-- y\n`-- z\n\n20 directories, 0 files\n'
treenew = 'sandbox\n|-- Q\n|   `-- S\n|       `-- D\n|           `-- F\n|               `-- G\n|                   `-- H\n|                       `-- J\n|                           `-- K\n|                               `-- L\n|                                   `-- M\n|-- a\n|-- e\n|-- i\n|-- o\n|-- p\n|-- r\n|-- t\n|-- u\n|-- y\n`-- z\n\n21 directories, 0 files\n'

try:
    if (subprocess.check_output(['tree', 'sandbox'], env=env).decode() == tree or
        subprocess.check_output(['tree', 'sandbox'], env=env).decode() == treenew):
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

