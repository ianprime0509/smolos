#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/core.h>
#include <kernel/fmt.h>

#include <kernel/arch/i686/gdt.h>

#include <kernel/arch/i686/idt.h>

#define MAXENT 32

typedef struct HndArg HndArg;
typedef struct IdtEnt IdtEnt;
typedef void (*IdtHnd)(HndArg*);

/* TODO: fill this in a bit more */
struct HndArg {
	uint16_t ds;
	uint32_t edx;
	uint32_t ecx;
	uint32_t ebx;
	uint32_t eax;
	uint32_t intno;
	uint32_t err;
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
	printf("No handler installed (INT 0x%X)\n", a->intno);
	printf("eax = %X, ebx = %X, ecx = %X, edx = %X\n", a->eax, a->ebx, a->ecx, a->edx);
}

static void
handledouble(HndArg *a)
{
	printf("eax = %X, ebx = %X, ecx = %X, edx = %X\n", a->eax, a->ebx, a->ecx, a->edx);
	panic("Double fault");
}

void lidt(uint64_t *tab, size_t sz);

void handler0(void);
void handler1(void);
void handler2(void);
void handler3(void);
void handler4(void);
void handler5(void);
void handler6(void);
void handler7(void);
void handler8(void);
void handler9(void);
void handler10(void);
void handler11(void);
void handler12(void);
void handler13(void);
void handler14(void);
void handler16(void);
void handler17(void);
void handler18(void);
void handler19(void);
void handler20(void);

#define HANDLE(n) tab[n] = makeent((IdtEnt){.handler = handler ## n, .codesel = GSCODE, .ring = 0})

void
idtinit(void)
{
	size_t i;

	for (i = 0; i < MAXENT; i++) {
		handlers[i] = handleempty;
		tab[i] = 0;
	}
	handlers[8] = handledouble;

	HANDLE(0);
	HANDLE(1);
	HANDLE(2);
	HANDLE(3);
	HANDLE(4);
	HANDLE(5);
	HANDLE(6);
	HANDLE(7);
	HANDLE(8);
	HANDLE(9);
	HANDLE(10);
	HANDLE(11);
	HANDLE(12);
	HANDLE(13);
	HANDLE(14);
	HANDLE(16);
	HANDLE(17);
	HANDLE(18);
	HANDLE(19);
	HANDLE(20);

	lidt(tab, sizeof(tab));
}
