#!/usr/bin/env python3

import hashlib
import os

env=dict(os.environ, LANG="C")

sandbox_summary = 'aacd88fece7c4b8f360ed4c1ff63f238617c86a54ee8dad4d6036a442dfc9c7a'


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

