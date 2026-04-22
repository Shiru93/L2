#!/usr/bin/env python3

import hashlib

filepath = "./sandbox/lorem"
hashsum = "e32f74a797be6ab461fb2ae5494d73f0f305d958b7dae314e3b80fc0934d3dcc"

try:
    hasher = hashlib.sha256()
    with open(filepath, 'rb') as f:
        buf = f.read()
        hasher.update(buf)
    if hasher.hexdigest() == hashsum:
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

