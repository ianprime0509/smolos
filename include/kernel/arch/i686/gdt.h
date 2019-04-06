/* gdt.h - GDT manipulation */

/* A 0-based index into a selector array. To get the actual selector number, multiply by 8. */
enum GdtSel {
	GSNULL,
	GSCODE,
	GSDATA,
	GSMAX,
};

typedef enum GdtSel GdtSel;

void gdtinit(void);
