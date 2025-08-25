CC = gcc
AS = nasm
LD = ld
CFLAGS = -Wall -Wextra -std=c11 -m64 -ffreestanding -fno-stack-protector -fno-pie
ASFLAGS = -f elf64
LDFLAGS = -nostdlib -z max-page-size=0x1000 -m elf_x86_64

KERNEL = kernel.elf

SRCDIR = src
BUILDDIR = build

KERNEL_SRCS = $(wildcard $(SRCDIR)/kernel/*.c) \
              $(wildcard $(SRCDIR)/drivers/*.c) \
              $(wildcard $(SRCDIR)/arch/x86_64/*.c)
KERNEL_OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(KERNEL_SRCS))
ASM_SRCS = $(wildcard $(SRCDIR)/arch/x86_64/*.asm)
ASM_OBJS = $(patsubst $(SRCDIR)/%.asm,$(BUILDDIR)/%.o,$(ASM_SRCS))

.PHONY: all clean run

all: $(BUILDDIR)/$(KERNEL)

$(BUILDDIR)/$(KERNEL): $(KERNEL_OBJS) $(ASM_OBJS)
	@mkdir -p $(@D)
	$(LD) $(LDFLAGS) -T $(SRCDIR)/arch/x86_64/linker.ld -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.asm
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)

run: all
	qemu-system-x86_64 -kernel $(BUILDDIR)/$(KERNEL) -serial stdio
