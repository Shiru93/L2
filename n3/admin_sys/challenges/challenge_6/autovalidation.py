#!/usr/bin/env python3

import hashlib
import os
import stat

env = dict(os.environ, LANG="C")

sandbox_summary = '4b56b894194769f1a3d66b5a9cf5d90f8afa8536f6f14f7b46b3999c370add2a'


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
            if stat.S_ISFIFO(os.stat(filepath).st_mode):
                L.append(hash256(filepath + '//' + 'da8da10c58930a51bb7c88c28873c6d614b7d743de14aef400211b022b8aa9b3'))
            else:
                L.append(hash256(filepath + '//' + hash256(hash256(open(filepath, 'rb').read()))))
    return hash256(''.join(sorted(L)))

try:
    # print(summary("./sandbox"))
    if summary("./sandbox") == sandbox_summary:
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

