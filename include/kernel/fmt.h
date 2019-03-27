/* fmt.h - formatted I/O */

size_t printf(const char *fmt, ...);
size_t vprintf(const char *fmt, va_list args);
size_t oprintf(void (*putc)(char), const char *fmt, ...);
size_t voprintf(void (*putc)(char), const char *fmt, va_list args);
