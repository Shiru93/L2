#!/usr/bin/env python3

import hashlib
import os

env=dict(os.environ, LANG="C")

sandbox_summary = '0b11a16a1fb79c10d8858cb1d34da16a1df515025711be284cd18664487258a2'


def hash256(s):
    hasher = hashlib.sha256()
    hasher.update(str(s).encode('utf-8'))
    return hasher.hexdigest()

def summary(directory):
    L = []
    for dirpath, dirnames, filenames in os.walk(directory, topdown=False):
        L.append(hash256(dirpath))
        for filename in filenames:
            filepath = dirpath + '/' + filename
            L.append(hash256(filepath + '//' + hash256(hash256(open(filepath, 'rb').read()))))
    return hash256(''.join(sorted(L)))

try:
    if summary("./sandbox") == sandbox_summary:
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

