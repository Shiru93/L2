#!/usr/bin/env python3

import hashlib
import os
import stat

env = dict(os.environ, LANG="C")

sandbox_summary = 'c41366eccef3f2235adb793e394425c76b55bb91f95238470db2da3e8701ba78'


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

