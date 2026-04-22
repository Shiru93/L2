#!/usr/bin/env python3

import hashlib
import os

env=dict(os.environ, LANG="C")

sandbox_summary = '914955c7cee5e2c61c89f1ac9de93d6009fa941ebddd695518f319c69ef84186'


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

