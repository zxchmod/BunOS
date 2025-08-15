# bunOS

bunOS — a lightweight graphical OS prototype designed for compact devices, such as headphone-case form factors.  
It features a simple GUI in 320×200 VGA Mode 13h, supports wallpapers, multiple languages, a custom app format (`.bunapp`), a microloader, an app registry, a demo antivirus, and persistent user settings stored on disk.

**Author:** NameSugar

## Quick Start

**Requirements:** GCC with `-m32` support and QEMU.

```bash
make
qemu-system-i386 -fda bunos.bin

## Demo & Controls

Arrow keys – navigate menus
Enter – select
S – open Settings
ESC – halt OS

In Settings, you can switch languages (English, Ukrainian, Korean, Russian, Hebrew) and change wallpapers.
Press Save to store settings to disk (last sector of floppy image).

bunOS is intended as a learning and demonstration project for compact device OS design.
```

## OS Structure
```
bunOS/
├── boot/                  # Microloader and boot-related files
│   ├── bootloader.asm
│   └── boot.img
├── src/                   # Source code of the kernel and GUI
│   ├── kernel.c
│   ├── gui.c
│   ├── filesystem.c
│   └── settings.c
├── apps/                  # Built-in apps and sample .bunapp applications
│   ├── antivirus.bunapp
│   └── demo_app.bunapp
├── include/               # Header files
│   └── bunos.h
├── Makefile               # Build instructions
├── README.md
└── .gitignore
```
