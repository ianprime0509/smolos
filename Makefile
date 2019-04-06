.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o .s

include config.mk

ASFLAGS =
CFLAGS = -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CPPFLAGS = -D$(TARGET)

all: kernel-all

clean: kernel-clean

KERNEL_DIR = src/kernel
include $(KERNEL_DIR)/build.mk

run: kernel-all
	$(QEMU) -d int -no-reboot -kernel $(KERNEL_DIR)/kernel.bin

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<
