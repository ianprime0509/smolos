#include <stddef.h>
#include <stdint.h>

#include <kernel/core.h>

#include <kernel/arch/i686/gdt.h>

#include <kernel/arch/i686/idt.h>

#define MAXENT 32

typedef struct HndArg HndArg;
typedef struct IdtEnt IdtEnt;
typedef void (*IdtHnd)(HndArg*);

/* TODO: fill this in a bit more */
struct HndArg {
	uint32_t intno;
};

/*
 * Only 32-bit interrupt gates are supported.
 */
struct IdtEnt {
	void (*handler)(void);
	GdtSel codesel;
	int ring;
};

IdtHnd handlers[MAXENT];

static uint64_t tab[MAXENT];

static uint64_t
makeent(IdtEnt ent)
{
	uint64_t ret;
	size_t offset;
	uint8_t flags;

	offset = (size_t)ent.handler;
	ret = offset & 0xFFFF;
	ret |= (((uint64_t)ent.codesel * 8) << 16);
	flags = 0x8E | (ent.ring << 5);
	ret |= ((uint64_t)flags << 40);
	ret |= ((uint64_t)((offset & 0xFFFF0000) >> 16) << 48);
	return ret;
}

static void
handleempty(HndArg *a)
{
	panic("No handler installed (INT 0x%X)", a->intno);
}

void lidt(uint64_t *tab, size_t sz);

void handler0(void);
void handler1(void);
void handler13(void);

#define HANDLE(n) tab[n] = makeent((IdtEnt){.handler = handler ## n, .codesel = GSCODE, .ring = 0})

void
idtinit(void)
{
	size_t i;

	for (i = 0; i < MAXENT; i++)
		handlers[i] = handleempty;

	HANDLE(0);
	HANDLE(1);
	HANDLE(13);

	lidt(tab, sizeof(tab));
}
