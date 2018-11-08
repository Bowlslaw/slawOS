#ifndef _ARCH_I386_IDT_H
#define _ARCH_I386_IDT_H

#define IDT_SIZE 256

#include <stdint.h>

 /* IDT table entry */
struct idt_entry {
	uint16_t base_low;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  type_attr;
	uint16_t base_high;
} __attribute__((packed));

 /** Pointer type used by `lidt` instuction */
struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct regs {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //Pushed by pusha
	uint32_t irqn, err;
	uint32_t eip, cs, eflags; // Pushed by CPU on interrupt
} __attribute__((packed));

/* ASM functions */
extern void idt_flush(uint32_t);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr33();

#endif
