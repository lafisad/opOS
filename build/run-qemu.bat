@echo off
REM Run opOS in QEMU (bootloader + kernel)
qemu-system-i386 -drive format=raw,file=opos.img
