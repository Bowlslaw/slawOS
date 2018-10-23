#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* Segment selectors */
#define KERNEL_CS 0x08

/* Define interrupt gate (handler) */
typedef struct {
  uint16_t low_offset; /* offset bits 0..15 */
  uint16_t sel;        /* kernel segment slector */
  uint8_t zero;        /* unused; always 0 */
  uint8_t flags;       /* type and attributes */
  uint16_t high_offset;/* offset bits 16..31 */
} __attribute__((packed)) idt_gate_t;

/* Pointer to array of interrupt handlers.
 * 'lidt' */
typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

/* Implemented in idt.c */
void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif
