#include <stdarg.h>
#include <stddef.h>

#include <fmt.h>
#include <term.h>

size_t
printf(const char *fmt, ...)
{
	va_list args;
	size_t n;

	va_start(args, fmt);
	n = vprintf(fmt, args);
	va_end(args);
	return n;
}

size_t
vprintf(const char *fmt, va_list args)
{
	return voprintf(termputc, fmt, args);
}

size_t
oprintf(void (*putc)(char), const char *fmt, ...)
{
	va_list args;
	size_t n;

	va_start(args, fmt);
	n = voprintf(putc, fmt, args);
	va_end(args);
	return n;
}

size_t
voprintf(void (*putc)(char), const char *fmt, va_list args)
{
	size_t n;

	n = 0;
	while (*fmt) {
		n++;
		putc(*fmt++);
	}
	return n;
}
