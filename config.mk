TARGET = i686

AS = $(TARGET)-elf-as
CC = $(TARGET)-elf-gcc
# TODO: this is not portable to other archs
QEMU = qemu-system-i386
