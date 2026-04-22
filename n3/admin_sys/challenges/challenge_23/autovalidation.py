#!/usr/bin/env python3

import hashlib

# cas particulier si "Voulez-vous" n'est pas coupé
almost_musset_hashsum = "28467f91ab84c6d7a9848256aa8f1bad7c376f3b5e1e194fe5461003fe2dbb0a"
almost_musset_filepath = "./sandbox/musset.txt"
try:
    hasher = hashlib.sha256()
    with open(almost_musset_filepath, 'rb') as f:
        buf = f.read()
        hasher.update(buf)
    if hasher.hexdigest() == almost_musset_hashsum:
        print("Attention au fait qu'un tiret peut séparer deux mots !")
except Exception:
    print('Essaie encore !')


# test normal
files_to_check= [
    ("./sandbox/musset.txt",
    "a92e922b819426cea7c20bd889b77be2a008c42f1255058d471b31e5cc8840b9"),
    ("./sandbox/sand.txt",
    "4f8c4587c9e9a2c601c0de97c5e67be0bde62ccbe14feab7a9bf3ce89586ff1a")
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

