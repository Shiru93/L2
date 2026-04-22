#!/usr/bin/env python3

import os, subprocess

env=dict(os.environ, LANG="C")

try:
    if (len(list(os.walk('sandbox2', topdown=False))) == 171
        and os.path.exists('./sandbox2/vCYabBG/XSdsOj/TrFHZLki/SkqlT/KvKESLd')
        and os.path.exists('./sandbox2/vCYabBG/ehIpQcOv/wwBpfizo/cDStkqV')
        and not os.path.exists('./sandbox')): 
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')

