#!/usr/bin/env python3

import hashlib
import os

env=dict(os.environ, LANG="C")

sandbox_summary = '51cfb78fc07a9015f98cfaa010fcf1a52879b8f33fbf021eb36b3e5c4f5761f7'


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

