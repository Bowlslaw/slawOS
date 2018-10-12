#ifndef IDT_H
#define IDT_H

#include "types.h"

/* Segment selectors */
#define KERNEL_CS 0x08

/* Define interrupt gate (handler) */
typedef struct {
  u16 low_offset; /* offset bits 0..15 */
  u16 sel;        /* kernel segment slector */
  u8 zero;        /* unused; always 0 */
  u8 flags;       /* type and attributes */
  u16 high_offset;/* offset bits 16..31 */
} __attribute__((packed)) idt_gate_t;

/* Pointer to array of interrupt handlers.
 * 'lidt' */
typedef struct {
  u16 limit;
  u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

/* Implemented in idt.c */
void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
