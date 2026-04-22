#!/usr/bin/env python3

import hashlib

try:
    hasher = hashlib.sha256()
    with open('./sandbox/zeros.bin', 'rb') as f:
        buf = f.read()
        hasher.update(buf)
    if hasher.hexdigest() == "30e14955ebf1352266dc2ff8067e68104607e750abb9d3b36582b8af909fcb58":
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

