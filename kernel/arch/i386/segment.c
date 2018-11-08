#include "segment.h"

struct segment_descriptor GDT[5];
struct gdt_ptr gdt_ptr;

struct segment_descriptor
make_descriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	struct segment_descriptor desc;

	desc.base_low = base & 0xFFFF;
	desc.base_middle = (base >> 16) & 0xFF;
	desc.base_high = (base >> 24) & 0xFF;
	desc.access = access;
	desc.limit_low = limit & 0xFFFF;
	desc.flag_limit_high = (limit >> 16) & 0x0F;
	desc.flag_limit_high |= flags & 0xF0;
	return desc;
}

void gdt_init(void) {
	/* Flat memory setup, suitable for SYSENTER/SYSEXIT */
	GDT[0] = make_descriptor(0, 0, 0, 0);
	GDT[1] = make_descriptor(0x0, 0xFFFFFFFF, SEG_KERNEL_CODE, SEG_FLAGS_32);
	GDT[2] = make_descriptor(0x0, 0xFFFFFFFF, SEG_KERNEL_DATA, SEG_FLAGS_32);
	GDT[3] = make_descriptor(0x0, 0xFFFFFFFF, SEG_USER_CODE, SEG_FLAGS_32);
	GDT[4] = make_descriptor(0x0, 0xFFFFFFFF, SEG_USER_DATA, SEG_FLAGS_32);

	gdt_ptr.base = (uint32_t)GDT;
	gdt_ptr.limit = sizeof(GDT) - 1;

	gdt_flush((uint32_t)&gdt_ptr);
}
