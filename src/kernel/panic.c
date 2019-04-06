#include <stdarg.h>
#include <stddef.h>

#include <kernel/fmt.h>

void hang(void);

void panic(const char *fmt, ...)
{
	va_list args;

	printf("PANIC: ");
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	hang();
}
