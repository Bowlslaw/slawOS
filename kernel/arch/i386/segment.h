#ifndef _ARCH_I386_GDT_J
#define _ARCH_I386_GDT_J

#include <stdint.h>

struct segment_descriptor {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  // P:1    - Present
  // DPL:2  - Descriptor Privilege Level (ring)
  // S:1    - Descriptor type
  // Type:4 - segment type
  uint8_t  access;
  // 4 bits of flags and 4 bits of limit high bits
  // flags:
  // 	G   - Granularity
  // 	D/B - Width (16 or 32 bits)
  // 	L   - Long (64 bits)
  // 	AVL - Available for system use
  uint8_t  flag_limit_high;
  uint8_t  base_high;
} __attribute__((packed));

// Segment types (type:4 in access field)
#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

 // Common descriptor access values
#define __SEG_KERNEL 0x90 // Kernel segment: P=1, DPL=0, S=1, type=TBD
#define SEG_KERNEL_CODE (__SEG_KERNEL | SEG_CODE_EXRD)
#define SEG_KERNEL_DATA (__SEG_KERNEL | SEG_DATA_RDWR)
#define __SEG_USER 0xF0 // User segment: P=1, DPL=3, S=1, type=TBD
#define SEG_USER_CODE (__SEG_USER | SEG_CODE_EXRD)
#define SEG_USER_DATA (__SEG_USER | SEG_DATA_RDWR)

 // Flags value
// Generic 32-bit segment: G=1, D/B=1 (32-bit), L=0 (not 64 bits), AVL=0
#define SEG_FLAGS_32 0xCF
// Pointer to GDT that will be loaded in gdtr
struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

void gdt_init(void);

extern void gdt_flush(uint32_t gdt_ptr);

#endif
