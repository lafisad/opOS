# Toolchain
CC = x86_64-elf-gcc
AS = nasm
LD = x86_64-elf-ld

# Directories
SRCDIR = src
BUILDDIR = build
MODULEDIR = modules
INCLUDEDIR = include

# Output files
KERNEL = kernel.elf
ISO = opos.iso

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -m64 -ffreestanding \
         -fno-stack-protector -fno-pie -fno-pic \
         -I$(INCLUDEDIR) -I$(SRCDIR)
ASFLAGS = -f elf64
LDFLAGS = -nostdlib -z max-page-size=0x1000 -m elf_x86_64 \
          -T $(SRCDIR)/arch/x86_64/linker.ld

# Source files
KERNEL_SRCS = $(wildcard $(SRCDIR)/kernel/*.c) \
              $(wildcard $(SRCDIR)/drivers/*.c) \
              $(wildcard $(SRCDIR)/arch/x86_64/*.c)

# Module files
MODULE_SRCS = $(wildcard $(MODULEDIR)/**/*.c)
MODULE_OBJS = $(patsubst $(MODULEDIR)/%.c,$(BUILDDIR)/%.o,$(MODULE_SRCS))

# Object files
KERNEL_OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(KERNEL_SRCS))
ASM_SRCS = $(wildcard $(SRCDIR)/arch/x86_64/*.asm)
ASM_OBJS = $(patsubst $(SRCDIR)/%.asm,$(BUILDDIR)/%.o,$(ASM_SRCS))

# Default target
.PHONY: all clean run iso

all: $(BUILDDIR)/$(KERNEL)

# Create ISO image
iso: all
	mkdir -p $(BUILDDIR)/isofiles/boot/grub
	cp $(BUILDDIR)/$(KERNEL) $(BUILDDIR)/isofiles/boot/
	echo 'set timeout=0' > $(BUILDDIR)/isofiles/boot/grub/grub.cfg
	echo 'set default=0' >> $(BUILDDIR)/isofiles/boot/grub/grub.cfg
	echo 'menuentry "opOS" {' >> $(BUILDDIR)/isofiles/boot/grub/grub.cfg
	echo '  multiboot /boot/$(KERNEL)' >> $(BUILDDIR)/isofiles/boot/grub/grub.cfg
	echo '  boot' >> $(BUILDDIR)/isofiles/boot/grub/grub.cfg
	echo '}' >> $(BUILDDIR)/isofiles/boot/grub/grub.cfg
	grub-mkrescue -o $(BUILDDIR)/$(ISO) $(BUILDDIR)/isofiles

# Link kernel
$(BUILDDIR)/$(KERNEL): $(KERNEL_OBJS) $(ASM_OBJS) $(MODULE_OBJS)
	@mkdir -p $(@D)
	$(LD) $(LDFLAGS) -o $@ $^

# Compile C files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile modules
$(BUILDDIR)/%.o: $(MODULEDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble ASM files
$(BUILDDIR)/%.o: $(SRCDIR)/%.asm
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR)

# Run in QEMU
run: all
	qemu-system-x86_64 -kernel $(BUILDDIR)/$(KERNEL) -serial stdio

# Run with ISO
run-iso: iso
	qemu-system-x86_64 -cdrom $(BUILDDIR)/$(ISO) -serial stdio
