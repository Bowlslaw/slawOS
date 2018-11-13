.global kbd_isr
kbd_isr:
    call kbd_isr_main
    iret

.extern isr_handler

isr_common_stub:
  /* Save regsiters in order:
   * EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI */
  pusha

  /* Save data segment descriptor */
  movw %ds, %ax
  pushl %eax

  /* load kernel segment descriptor */
  movw $(0x2 * 8), %ax
  movw %ax, %ds
  movw %ax, %es
  movw $(0x1 * 8), %ax
  movw %ax, %fs
  movw %ax, %gs

  /* Push regs argument for isr_handler */
  pushl %esp
  call isr_handler
  addl $4, %esp

  popl %eax

  /* Reload original data segment descriptor */
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  /* Clean up pushed error code */
  popa
  add $8, %esp
  sti
  iret

/* define a macro, taking one parameter */
.macro ISR_NOERRCODE n
.global isr\n
isr\n:
  cli
  /* When there is no error code provided, explicitly push 0 to unify ISR
   * stacks of ISR_NOERRCODE and ISR_ERRCODE */
  pushl $0
  pushl $\n
  jmp isr_common_stub
.endm

.macro ISR_ERRCODE n
.global isr\n
isr\n:
  cli
  /* Error code is already pushed before interrupt vector number */
  pushl \n
  jmp isr_common_stub
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 33
