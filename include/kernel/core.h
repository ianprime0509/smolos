/* core.h - core kernel functions */

#define USED(x) ((void)(x))

void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);

void hang(void);
void panic(const char *fmt, ...);
