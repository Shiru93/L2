#!/usr/bin/env python3

import hashlib
import os, subprocess

env=dict(os.environ, LANG="C")




files_to_check= [
    ("./sandbox/qDuqtKxY", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/BRUZuDqd", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/eAVYdGCN", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/ujjqTYMk", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/xUZJevT", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/RaiQydVG", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/tuVIfmXi", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/tbWwEaV", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/ZXHwculfrCzi/JaKxReLV", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/ZXHwculfrCzi/ZpqdWAnC", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/ZXHwculfrCzi/Fizjgfm", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/ZXHwculfrCzi/OxrfUy", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/UKPlvBuk", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/GrTLzyOugpbAlb/prdkHicI", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/GrTLzyOugpbAlb/EMwQSAX", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/GrTLzyOugpbAlb/dgHkKNv", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/GrTLzyOugpbAlb/HAYzrDI", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/clVgaZmxRtXtO/kYZTRRtB", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/CEbFWJbbt/DrmRiGMJ", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/CEbFWJbbt/aIWgqAq", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/CEbFWJbbt/IWfwFj", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/CEbFWJbbt/mcezn", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/OLzXmKHC", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/snyMcuOSuiwCI/fEcgof", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/snyMcuOSuiwCI/yWkKKsg", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/snyMcuOSuiwCI/JNXCcPZf", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/snyMcuOSuiwCI/BBDcuNH", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/ViWlN", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/LROEiwEpoeTIja/NMeFexZ", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/LROEiwEpoeTIja/OpHUGU", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/LROEiwEpoeTIja/jBxPvT", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/uyfByRgKlUQ/VsvFuUOQE/OlFwQ", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/yDRAF", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/nWcgmC", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/UMRMeNKkClGDy/VuaeqJxsuHy/gWySeB", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/UMRMeNKkClGDy/VuaeqJxsuHy/OyhBYt", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/UMRMeNKkClGDy/VuaeqJxsuHy/dsoXXvOj", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/zJJNEv", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/DLCpaB", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/oAduGm", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/TlxagCCigrP/RMFNcP", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/EzHQMpunxQY/TlxagCCigrP/RWXrtZD", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/EzHQMpunxQY/TlxagCCigrP/FFCoxliN", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/bkJirGw", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/BtLXCq", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/WzMik", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/rcjKdsxqPeyZh/DipGz", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/rcjKdsxqPeyZh/nsXeA", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/rcjKdsxqPeyZh/BvuqnbeE", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/rcjKdsxqPeyZh/ksLFLgkZ", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/qBMgyozweeREGS/TmIFz", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/qBMgyozweeREGS/oMsfpev", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/qBMgyozweeREGS/FpTDLK", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/qBMgyozweeREGS/SNXZe", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/EzHQMpunxQY/rBHtrWYgX/nSrddY", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/EzHQMpunxQY/fUIOmbKl", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/EzHQMpunxQY/CbrAXD", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/WZWxRfm", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/RqZfOsGc", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/EvZiFQVpS/DvzeBc", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/EvZiFQVpS/jnkrH", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/EvZiFQVpS/ajCLP", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/jEUqtv", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/drRPtpAo", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/fojCj", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/mZOMjpOEGE/MfaiJj", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/mZOMjpOEGE/SIiELv", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/mZOMjpOEGE/UQOGFMk", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/AlVKObkZCOWujw/XsxPeWdL", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/hCmahgVG", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/zhmARDX", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/WHobn", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/HUgdPAj", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/AfZRfsVdK/VFladEz", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/AfZRfsVdK/iDXnjDK", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/AfZRfsVdK/mcjHIB", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/AWigRSH", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/EUcNEs", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/uFFJSRNw", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/VSAkR", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/MFqnoDyGMlUua/CanlTmK", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/MFqnoDyGMlUua/HOwIHTzm", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/MFqnoDyGMlUua/QYeWnE", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/MFqnoDyGMlUua/hhoVrgwp", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/OqvTWIjZokP/cUOFSl", "1de2c6b9a0b398e60f9b33b2b8a63df097600357b5a9c41ff4ecc75548ad617c"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/OqvTWIjZokP/EVfyYtZ", "a4f99eaf4d9790c4be9ea80b1cffbd962d32f6932afc9a539f5d69020917ec84"),
    ("./sandbox/bmxAdBNkIAm/HcXxiorUl/KANupHwGXuQpr/OqvTWIjZokP/PZgDfjO", "0a848453613a65d12cf543cc46fadaa4d76934fc751bf74ececd3625d047a600"),
]


try:
    success = True
    for filepath, hashsum in files_to_check:
        hasher = hashlib.sha256()
        with open(filepath, 'rb') as f:
            buf = f.read()
            hasher.update(buf)
        success = success and (hasher.hexdigest() == hashsum)
    if success and int(subprocess.check_output(['du','-s', 'sandbox'],env=env).split()[0].decode('utf-8')) < 400:
        print('Félicitations !')
    else:
        print('Essaie encore !')
except Exception:
    print('Essaie encore !')
