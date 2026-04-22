#!/usr/bin/env python3

import hashlib

files_to_check= [
    ("./sandbox/kiss_lo.cast",
    "1409c46b8a3901eb6a73a426c1d05f6be74eb067a7faf12adcacaf5f95714bf8")
]

try:
    success = True
    for filepath, hashsum in files_to_check:
        hasher = hashlib.sha256()
        with open(filepath, 'rb') as f:
            buf = f.read()
            hasher.update(buf)
        success = success and (hasher.hexdigest() == hashsum)
    if success:
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

