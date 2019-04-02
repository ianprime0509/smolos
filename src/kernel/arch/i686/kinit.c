#include <stdarg.h>
#include <stddef.h>

#include <kernel/fmt.h>
#include <kernel/term.h>

#include <kernel/arch/i686/gdt.h>

void
kinit(void)
{
	terminit();
	printf("Initialized terminal\n");
	gdtinit();
	printf("Set up GDT\n");
}
