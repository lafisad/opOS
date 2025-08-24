

# opOS build configuration - Bootable AF Edition
NASM=nasm
CC=i686-elf-gcc
LD=i686-elf-ld

# Flags
NASMFLAGS=-f elf32
CFLAGS=-ffreestanding -O2 -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
LDFLAGS=-T link.ld -nostdlib

# Source files
BOOT_SRC=src/boot.asm
ENTRY_SRC=src/entry.asm
KERNEL_SRC=src/kernel_bare.c
MODULE_SYSTEM_SRC=src/module_system.c
SECURITY_SRC=src/modules/security/security.c
HWSCAN_SRC=src/modules/hardware_scanner/hwscan.c
SHELL_SRC=src/modules/shell.c

# Object files
BOOT_BIN=build/boot.bin
ENTRY_OBJ=build/entry.o
KERNEL_OBJ=build/kernel.o
MODULE_SYSTEM_OBJ=build/module_system.o
SECURITY_OBJ=build/security.o
HWSCAN_OBJ=build/hwscan.o
SHELL_OBJ=build/shell.o

# Final output
KERNEL_BIN=build/kernel.bin
OS_IMG=build/opos.img

.PHONY: all clean run

all: $(OS_IMG)

# Compile assembly
$(BOOT_BIN): $(BOOT_SRC)
	$(NASM) -f bin -o $@ $<

$(ENTRY_OBJ): $(ENTRY_SRC)
	$(NASM) $(NASMFLAGS) -o $@ $<

# Compile C sources
$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MODULE_SYSTEM_OBJ): $(MODULE_SYSTEM_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(SECURITY_OBJ): $(SECURITY_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(HWSCAN_OBJ): $(HWSCAN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(SHELL_OBJ): $(SHELL_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Link everything
$(KERNEL_BIN): $(ENTRY_OBJ) $(KERNEL_OBJ) $(MODULE_SYSTEM_OBJ) $(SECURITY_OBJ) $(HWSCAN_OBJ) $(SHELL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Create bootable image
$(OS_IMG): $(BOOT_BIN) $(KERNEL_BIN)
	copy /b $(BOOT_BIN)+$(KERNEL_BIN) $(OS_IMG) >nul

clean:
	del /Q build\*.*

run:
	qemu-system-i386 -drive format=raw,file=$(OS_IMG)
