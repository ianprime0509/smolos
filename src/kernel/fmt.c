#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

#include <kernel/fmt.h>
#include <kernel/term.h>

static size_t
printuint(void (*putc)(char), unsigned int u, unsigned int base, int caps)
{
	static const char upper[16] = "0123456789ABCDEF";
	static const char lower[16] = "0123456789abcdef";
	char buf[sizeof(u) * CHAR_BIT];
	size_t pos, n;

	if (base == 0 || base > 16)
		return 0;
	if (u == 0) {
		putc('0');
		return 1;
	}

	pos = n = 0;
	while (u > 0) {
		buf[pos++] = (caps ? upper : lower)[u % base];
		u /= base;
	}
	while (pos-- > 0) {
		putc(buf[pos]);
		n++;
	}

	return n;
}

static size_t
printint(void (*putc)(char), int d, unsigned int base, int caps)
{
	if (d >= 0) {
		return printuint(putc, d, base, caps);
	} else {
		putc('-');
		/* We can't just do -INT_MIN (overflow) */
		return printuint(putc, -(d + 1) + 1, base, caps);
	}
}

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
	int infmt;

	n = 0;
	infmt = 0;
	while (*fmt)
		if (infmt) {
			infmt = 0;
			switch (*fmt++) {
			case 'd':
				printint(putc, va_arg(args, int), 10, 0);
				break;
			case 'u':
				printuint(putc, va_arg(args, unsigned int), 10, 0);
				break;
			case 'x':
				printuint(putc, va_arg(args, unsigned int), 16, 0);
				break;
			case 'X':
				printuint(putc, va_arg(args, unsigned int), 16, 1);
				break;
			case '%':
				n++;
				putc('%');
				break;
			}
		} else {
			if (*fmt == '%') {
				infmt = 1;
				fmt++;
			} else {
				putc(*fmt++);
				n++;
			}
		}

	return n;
}
