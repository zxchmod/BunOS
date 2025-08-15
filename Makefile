CC = gcc
CFLAGS = -ffreestanding -m32 -O2 -Wall -Wextra -fno-stack-protector -fno-pic -fno-builtin
LDFLAGS = -Ttext 0x1000 --oformat=binary

SRC = src/boot.c src/kernel.c src/gfx.c src/input.c src/power.c src/locale.c src/ui.c src/app.c src/antivirus.c src/storage.c
OBJ = $(SRC:.c=.o)
BIN = bunos.bin

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	ld $(OBJ) $(LDFLAGS) -o $(BIN)

run: all
	qemu-system-i386 -fda $(BIN)

clean:
	rm -f $(OBJ) $(BIN)
