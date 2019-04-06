#include <stdarg.h>
#include <stddef.h>

#include <kernel/core.h>
#include <kernel/fmt.h>

void
kmain(void)
{
	printf("Kernel booted\n");
	__asm__ volatile ("int $0xD");

	panic("Oh no!");
}
