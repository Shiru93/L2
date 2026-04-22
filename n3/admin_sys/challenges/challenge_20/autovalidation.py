#!/usr/bin/env python3

import hashlib

filepath = "./sandbox/compact"
hashsum = "2a4a9b0855c51f3320d3da09a8a57ab22b62103b084a6c0736e8016838ffe6d6"

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

