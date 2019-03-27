#include <stddef.h>

#include <kernel/core.h>

void *
memcpy(void *dest, const void *src, size_t n)
{
	void *ret;
	unsigned char *d;
	const unsigned char *s;

	ret = dest;
	d = dest;
	s = src;
	while (n-- > 0)
		*d++ = *s++;
	return ret;
}

void *
memmove(void *dest, const void *src, size_t n)
{
	void *ret;
	unsigned char *d;
	const unsigned char *s;

	ret = dest;
	d = dest;
	s = src;
	if (d > s) {
		d += n;
		s += n;
		while (n-- > 0)
			*--d = *--s;
	} else {
		while (n-- > 0)
			*d++ = *s++;
	}
	return ret;
}
