.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o .s

include config.mk

ASFLAGS =
CFLAGS = -Iinclude -std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: kernel-all

clean: kernel-clean

KERNEL_DIR = src/kernel
include $(KERNEL_DIR)/build.mk

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<
