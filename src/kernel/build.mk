KERNEL_ARCH_DIR=$(KERNEL_DIR)/arch/$(TARGET)
include $(KERNEL_ARCH_DIR)/build.mk

KERNEL_BIN = $(KERNEL_DIR)/kernel.bin
KERNEL_LINK_LD = $(KERNEL_ARCH_DIR)/link.ld
KERNEL_OBJS = $(KERNEL_ARCH_OBJS) \
	$(KERNEL_DIR)/kmain.o

kernel-all: $(KERNEL_BIN)

kernel-clean:
	rm -f $(BOOT_OBJ) $(KERNEL_OBJS) $(KERNEL_BIN)

$(KERNEL_BIN): $(KERNEL_LINK_LD) $(BOOT_OBJ) $(KERNEL_OBJS)
	$(CC) -T $(KERNEL_LINK_LD) -o $(KERNEL_BIN) -ffreestanding -O2 -nostdlib $(BOOT_OBJ) $(KERNEL_OBJS) -lgcc
