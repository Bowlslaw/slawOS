  ;; Defined in isr.c
[extern isr_handler]
[extern irq_handler]

  ;; Common ISR code
isr_common_stub:
  ;; 1) Save CPU state
  pusha                         ; push edi, esi, ebp, esp, ebx, edx, ecx, eax
  mov ax, ds                    ; lower 16-bits of eax = ds
  push eax                      ; save data segmant descriptor
  mov ax, 0x10                  ; kernel data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ;; 2) Call C handler
  call isr_handler

  ;; 3) Restore state
  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  popa
  add esp, 8                    ; clean up pushed error code and ISR number
  sti
  iret                          ; pop: CS, EIP, EFLAGS, SS, ESP

irq_common_stub:
  pusha
  mov ax, ds
  push eax
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  call irq_handler
  pop ebx
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx
  popa
  add esp, 8
  sti
  iret

  ;; Some interrupts push an error code onto the stack, but other don't.
  ;; So, we push a dummy code for those which don't to maintain consistent stack
  global isr0
  global isr1
  global isr2
  global isr3
  global isr4
  global isr5
  global isr6
  global isr7
  global isr8
  global isr9
  global isr10
  global isr11
  global isr12
  global isr13
  global isr14
  global isr15
  global isr16
  global isr17
  global isr18
  global isr19
  global isr20
  global isr21
  global isr22
  global isr23
  global isr24
  global isr25
  global isr26
  global isr27
  global isr28
  global isr29
  global isr30
  global isr31

  ;; IRQs
  global irq0
  global irq1
  global irq2
  global irq3
  global irq4
  global irq5
  global irq6
  global irq7
  global irq8
  global irq9
  global irq10
  global irq11
  global irq12
  global irq13
  global irq14
  global irq15

  ;; 0: Divide by Zero
isr0:
  cli
  push byte 0
  push byte 0
  jmp isr_common_stub

  ;; 1: Debug
isr1:
  cli
  push byte 0
  push byte 1
  jmp isr_common_stub

  ;; 2: Non Maskable
isr2:
  cli
  push byte 0
  push byte 2
  jmp isr_common_stub

  ;; 3: Int 3
isr3:
  cli
  push byte 0
  push byte 3
  jmp isr_common_stub

  ;; 4: INTO
isr4:
  cli
  push byte 0
  push byte 4
  jmp isr_common_stub

  ;; 5: Out of Bounds
isr5:
  cli
  push byte 0
  push byte 5
  jmp isr_common_stub

  ;; 6: Invalid Opcode
isr6:
  cli
  push byte 0
  push byte 6
  jmp isr_common_stub

  ;; 7: Coprocessor Not Available
isr7:
  cli
  push byte 0
  push byte 7
  jmp isr_common_stub

  ;; 8: Double Fault Exception
isr8:
  cli
  push byte 0
  push byte 8
  jmp isr_common_stub

  ;; 9: Coprocessor Segment Overrun
isr9:
  cli
  push byte 0
  push byte 9
  jmp isr_common_stub

  ;; 10: Bad TSS Exception
isr10:
  cli
  push byte 0
  push byte 10
  jmp isr_common_stub

  ;; 11: Segment Not Present
isr11:
  cli
  push byte 0
  push byte 11
  jmp isr_common_stub

  ;; 12: Stack Fault
isr12:
  cli
  push byte 0
  push byte 12
  jmp isr_common_stub

  ;; 13: General Protection Fault
isr13:
  cli
  push byte 0
  push byte 13
  jmp isr_common_stub

  ;; 14: Page Fault
isr14:
  cli
  push byte 0
  push byte 14
  jmp isr_common_stub

  ;; 15: Reserved
isr15:
  cli
  push byte 0
  push byte 15
  jmp isr_common_stub

  ;; 16: Floating Point
isr16:
  cli
  push byte 0
  push byte 16
  jmp isr_common_stub

  ;; 17: Alignment Check
isr17:
  cli
  push byte 0
  push byte 17
  jmp isr_common_stub

  ;; 18: Machine Check
isr18:
  cli
  push byte 0
  push byte 18
  jmp isr_common_stub

  ;; 19: Reserved
isr19:
  cli
  push byte 0
  push byte 19
  jmp isr_common_stub

  ;; 20: Reserved
isr20:
  cli
  push byte 0
  push byte 20
  jmp isr_common_stub

  ;; 21: Reserved
isr21:
  cli
  push byte 0
  push byte 21
  jmp isr_common_stub

  ;; 22: Reserved
isr22:
  cli
  push byte 0
  push byte 22
  jmp isr_common_stub

  ;; 23: Reserved
isr23:
  cli
  push byte 0
  push byte 23
  jmp isr_common_stub

  ;; 24: Reserved
isr24:
  cli
  push byte 0
  push byte 24
  jmp isr_common_stub

  ;; 25: Reserved
isr25:
  cli
  push byte 0
  push byte 25
  jmp isr_common_stub

  ;; 26: Reserved
isr26:
  cli
  push byte 0
  push byte 26
  jmp isr_common_stub

  ;; 27: Reserved
isr27:
  cli
  push byte 0
  push byte 27
  jmp isr_common_stub

  ;; 28: Reserved
isr28:
  cli
  push byte 0
  push byte 28
  jmp isr_common_stub

  ;; 29: Reserved
isr29:
  cli
  push byte 0
  push byte 29
  jmp isr_common_stub

  ;; 30: Reversed
isr30:
  cli
  push byte 0
  push byte 30
  jmp isr_common_stub

  ;; 31: Reverved
isr31:
  cli
  push byte 0
  push byte 31
  jmp isr_common_stub

  ;; IRQ handlers
irq0:
  cli
  push byte 0
  push byte 32
  jmp irq_common_stub

irq1:
	cli
	push byte 1
	push byte 33
	jmp irq_common_stub

irq2:
	cli
	push byte 2
	push byte 34
	jmp irq_common_stub

irq3:
  cli
  push byte 3
  push byte 35
  jmp irq_common_stub

irq4:
  cli
  push byte 4
  push byte 36
  jmp irq_common_stub

irq5:
  cli
  push byte 5
  push byte 37
  jmp irq_common_stub

irq6:
  cli
  push byte 6
  push byte 38
  jmp irq_common_stub

irq7:
  cli
  push byte 7
  push byte 39
  jmp irq_common_stub

irq8:
  cli
  push byte 8
  push byte 40
  jmp irq_common_stub

irq9:
  cli
  push byte 9
  push byte 41
  jmp irq_common_stub

irq10:
  cli
  push byte 10
  push byte 42
  jmp irq_common_stub

irq11:
  cli
  push byte 11
  push byte 43
  jmp irq_common_stub

irq12:
  cli
  push byte 12
  push byte 44
  jmp irq_common_stub

irq13:
  cli
  push byte 13
  push byte 45
  jmp irq_common_stub

irq14:
  cli
  push byte 14
  push byte 46
  jmp irq_common_stub

irq15:
  cli
  push byte 15
  push byte 47
  jmp irq_common_stub
