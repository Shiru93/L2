#!/usr/bin/env python3

import os, subprocess

env=dict(os.environ, LANG="C")

sandbox = "./sandbox/"
to_remove = "./sandbox/inutile/"

if os.path.isdir(sandbox) and not os.path.isdir(to_remove):
    print('Félicitations !')
else:
    print('Essaie encore !')

