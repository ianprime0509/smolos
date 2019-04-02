#include <stddef.h>
#include <stdint.h>

#include <kernel/arch/i686/gdt.h>

/* GDT selector type */
enum GdtType {
	TYPE_DATA = 0,
	TYPE_CODE = 1,
};

typedef struct GdtEnt GdtEnt;
typedef enum GdtType GdtType;

/*
 * Some restrictions of this abstraction:
 *
 * - Only 32-bit protected mode selectors are supported
 * - Only limits with page granularity are supported
 * - The direction/conforming bit is always 0
 * - The R/W bit is always 1 (all code segments are readable
 *   and all data segments are writable)
 */
struct GdtEnt {
	uint32_t offset;
	uint32_t limit;
	GdtType type;
	uint8_t ring;
};

enum {
	ENT_NULL,
	ENT_CODE,
	ENT_DATA,
	ENT_MAX,
};

static uint64_t tab[ENT_MAX];

static uint64_t
makeent(GdtEnt ent)
{
	uint64_t ret;
	uint8_t flags;

	ret = ent.limit & 0xFFFF;
	ret |= ((uint64_t)(ent.offset & 0xFFFFFF) << 16);
	flags = 0x92 | (ent.ring << 5) | (ent.type << 3);
	ret |= ((uint64_t)flags << 40);
	ret |= ((uint64_t)((ent.limit & 0xF0000) >> 16) << 48);
	ret |= ((uint64_t)0xC << 52);
	ret |= ((uint64_t)((ent.offset & 0xF000000) >> 24) << 56);
	return ret;
}

void lgdt(uint64_t *tab, size_t sz);
void reloadsegs(uint16_t code, uint16_t data);

void
gdtinit(void)
{
	tab[ENT_NULL] = 0;
	tab[ENT_CODE] = makeent((GdtEnt){.offset = 0, .limit = 0xFFFFFFFF, .type = TYPE_CODE, .ring = 0});
	tab[ENT_DATA] = makeent((GdtEnt){.offset = 0, .limit = 0xFFFFFFFF, .type = TYPE_DATA, .ring = 0});

	lgdt(tab, sizeof(tab));
	reloadsegs(ENT_CODE, ENT_DATA);
}
