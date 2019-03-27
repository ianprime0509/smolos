/* term.h - text terminal manipulation */

void terminit(void);

void termclear(void);
void termgetsize(size_t *rows, size_t *cols);
void termmove(size_t y, size_t x);
void termputc(char c);
