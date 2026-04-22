#!/usr/bin/env python3

import os

try:
    if os.stat('./sandbox/hop').st_ino != os.stat('./sandbox/rep/../hop').st_ino:
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

