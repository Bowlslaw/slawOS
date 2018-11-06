#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "idt.h"
#include "interrupts.h"

#include <kernel/tty.h>

extern void kbd_isr_main(void);

static struct idt_entry IDT[IDT_SIZE];

static void idt_set_gate(int num, uint32_t base, uint16_t selector, uint8_t type_attr) {
	IDT[num].base_low = base & 0xFFFF;
	IDT[num].base_high = (base >> 16) & 0xFFFF;
	IDT[num].selector = selector;
	IDT[num].zero = 0x00;
 	// TODO: it must be type_attr | 0x60 to set DPL=3 in user-mode
	IDT[num].type_attr = type_attr;
}

void idt_init(void) {
	struct idt_ptr idt_ptr;

 	memset(IDT, 0, sizeof(IDT));

 	idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
	idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
	idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
	idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
	idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
	idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
	idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
	idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
	idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	/* Keyboard IDT entry */
	idt_set_gate(0x21, (uint32_t)isr33, 0x08, 0x8E);

 	idt_ptr.base = (uint32_t)&IDT;
	idt_ptr.limit = sizeof(IDT) - 1;
	idt_flush((uint32_t)&idt_ptr);
}

void pic_init() {
  /* ICW1 - begin initialization */
  port_byte_out(PIC1_CMD, 0x11);
  port_byte_out(PIC2_CMD, 0x11);

  /* ICW2 - remap offset address of IDT
   * In x86 protected mode, we have to remap the PICs after 0x20 because
   * Intel has designated the first 32 interrupts as "reserved" for CPU exceptions
   */
  port_byte_out(PIC1_DATA, 0x20);
  port_byte_out(PIC2_DATA, 0x28);

  /* OCW3 - set up cascading */
  port_byte_out(PIC1_DATA, 0x04);
  port_byte_out(PIC2_DATA, 0x02);
  /*
   * port_byte_out(PIC1_DATA, 0x0);
   * port_byte_out(PIC2_DATA, 0x0);
  */

  /* ICW4 - environment info */
  port_byte_out(PIC1_DATA, 0x01);
  port_byte_out(PIC2_DATA, 0x01);

  /* mask interrupts */
  port_byte_out(PIC1_DATA, 0xFF);
  port_byte_out(PIC2_DATA, 0xFF);
}

void interrupts_init(void) {
  idt_init();
  pic_init();

  /* 0xfd = 11111101 - Enable only IRQ1 (kbd) */
  port_byte_out(PIC1_DATA, 0xFD);
  //port_byte_out(PIC2_DATA, 0xff);

  /* Enable interrupts */
  asm volatile ("sti");
}

/*void isr_handler(struct regs *r)*/
void isr_handler(struct regs *r) {
  int irqn = (int)r->irqn;
  printf("INT%d\n", irqn);

  /* write EOI */
  port_byte_out(PIC1_CMD, 0x20);

  switch(irqn) {
  case 0x21:
	kbd_isr_main();
	break;

  default:
	printf("Unknown interrupt %d\n", irqn);
	break;
  }
}


