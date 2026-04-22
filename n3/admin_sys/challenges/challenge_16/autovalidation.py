#!/usr/bin/env python3

import os, subprocess

env=dict(os.environ, LANG='C', LC_ALL='C')

try:
    if all(subprocess.check_output(['du','-sh', path], env=env).split()[0].decode('utf-8') == '1.1M' for path in ['.', 'sandbox', 'sandbox2']):
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

