BOOT_OBJ = $(KERNEL_ARCH_DIR)/boot.o

KERNEL_ARCH_OBJS = \
	$(KERNEL_ARCH_DIR)/gdt.o \
	$(KERNEL_ARCH_DIR)/gdt-asm.o \
	$(KERNEL_ARCH_DIR)/hang.o \
	$(KERNEL_ARCH_DIR)/kinit.o \
	$(KERNEL_ARCH_DIR)/idt.o \
	$(KERNEL_ARCH_DIR)/idt-asm.o \
	$(KERNEL_ARCH_DIR)/port.o \
	$(KERNEL_ARCH_DIR)/term.o
