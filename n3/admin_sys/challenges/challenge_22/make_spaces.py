#!/usr/bin/env python3

import os
import random

def spacify(directory):
    L = []
    for dirpath, dirnames, filenames in os.walk(directory, topdown=False):
        for filename in filenames:
            filepath = dirpath + '/' + filename
            # print(filepath)
            with open(filepath, 'r') as f:
                s = f.read()
            t = ''.join([random.choice(['']*10 + [' '*random.randint(1,10)]) +'\n' if i == '\n' else i for i in s])
            with open(filepath, 'w') as f:
                f.write(t)

spacify("./sandbox")

