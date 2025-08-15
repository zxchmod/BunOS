# bunOS

bunOS — tiny graphical OS prototype for compact devices (headphone-case form factor).  
It runs in 320×200 VGA Mode 13h and demonstrates a small GUI, wallpapers, multi-language support, a simple app format (`.bunapp`), a microloader, app registry, a demo antivirus and persistent user settings stored on disk.

Author: NameSugar

## Quick start

Requirements: GCC with `-m32` support and QEMU.

```bash
make
qemu-system-i386 -fda bunos.bin
```

Use arrow keys to navigate, Enter to select, `s` to open Settings, ESC to halt. In Settings you can switch language (English, Ukrainian, Korean, Russian, Hebrew) and wallpaper; Save writes settings to disk (last sector of floppy image).
