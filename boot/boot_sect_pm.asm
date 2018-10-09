  ;; Boot and enter into 32-bit protected mode
[org 0x7c00]

  mov bp, 0x9000
  mov sp, bp

  mov bx, MSG_REAL_MODE
  call print_string

  call switch_pm

  jmp $

	%include "print/print_string.asm"
	%include "print/print_string_pm.asm"
	%include "print/print_hex.asm"
	%include "gdt.asm"
	%include "protected_mode.asm"

  [bits 32]
BEGIN_PM:
  mov ebx, MSG_PROT_MODE
  call print_string_pm

  jmp $

  MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
  MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode", 0

  ;; Bootsector padding
  times 510-($-$$) db 0
  dw 0xaa55
