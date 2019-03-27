#include <stdarg.h>
#include <stddef.h>

#include <kernel/fmt.h>
#include <kernel/term.h>

void
kmain(void)
{
	terminit();
	printf("Hello, world!\n");
	printf("Test: %X\n", 0xAB12);
}
