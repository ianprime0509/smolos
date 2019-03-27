#include <stddef.h>
#include <stdint.h>

#include <kernel/core.h>
#include <kernel/term.h>

#define TROWS 25
#define TCOLS 80

#define TABLEN 8

enum Color {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

typedef enum Color Color;

static uint16_t *termbuf = (uint16_t *)0xB8000;
static Color fgcolor = LIGHT_GREY;
static Color bgcolor = BLACK;
static size_t row, col;

static uint16_t
makechar(char c, Color fg, Color bg)
{
	return (unsigned char)c | ((uint16_t)(fg | bg << 4) << 8);
}

static void
newline(void)
{
	uint16_t clear;
	size_t i;

	col = 0;
	if (row < TROWS - 1) {
		row++;
		return;
	}
	row = TROWS - 1;

	clear = makechar(' ', fgcolor, bgcolor);
	for (i = 0; i < TROWS - 1; i++)
		memcpy(termbuf + (i - 1) * TCOLS, termbuf + i * TCOLS, TCOLS * sizeof(*termbuf));
	for (i = 0; i < TCOLS; i++)
		termbuf[i + (TROWS - 1) * TCOLS] = clear;
}

static void
tab(void)
{
	col = (col + TABLEN - 1) / TABLEN * TABLEN;
	if (col >= TCOLS)
		col = TCOLS - 1;
}

void
terminit(void)
{
	termclear();
}

void
termclear(void)
{
	uint16_t clear;
	size_t i;

	row = col = 0;
	clear = makechar(' ', fgcolor, bgcolor);
	for (i = 0; i < TROWS * TCOLS; i++)
		termbuf[i] = clear;
}

void
termgetsize(size_t *rows, size_t *cols)
{
	if (rows)
		*rows = TROWS;
	if (cols)
		*cols = TCOLS;
}

void
termmove(size_t y, size_t x)
{
	if (y >= TROWS)
		y = TROWS - 1;
	if (x >= TCOLS)
		x = TCOLS - 1;
	row = y;
	col = x;
}

void
termputc(char c)
{
	if (c == '\n') {
		newline();
	} else if (c == '\t') {
		tab();
	} else {
		termbuf[TCOLS * row + col++] = makechar(c, fgcolor, bgcolor);
		if (col >= TCOLS)
			newline();
	}
}
