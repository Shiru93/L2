#!/usr/bin/env python3

import os, filecmp

env=dict(os.environ, LANG="C")

os.chdir('sandbox')

try:
    if (os.path.getsize('aa') != 0 and 
        os.path.getsize('bb') != 0 and
        os.path.getsize('cc') != 0 and 
        os.path.getsize('dd') != 0 and
        os.stat('aa').st_ino == os.stat('bb').st_ino and
        os.stat('cc').st_ino != os.stat('bb').st_ino and
        filecmp.cmp('cc', 'bb') and
        not filecmp.cmp('dd', 'bb')):
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

