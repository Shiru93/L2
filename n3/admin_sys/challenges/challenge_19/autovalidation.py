#!/usr/bin/env python3

import hashlib

filepath = "./sandbox/sans_commentaire"
hashsum = "2eceb9b4d913154a486763b681bc693f3334a197ab3fb1e537812a33fcac2c07"

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

