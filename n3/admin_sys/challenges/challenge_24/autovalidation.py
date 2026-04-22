#!/usr/bin/env python3

import hashlib

files_to_check= [("./sandbox/willy.txt", "4eadb2b71bb4187a5099dbe1fca6f123ffee1510ce3001eda34b2860eac7e3b1")]

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

