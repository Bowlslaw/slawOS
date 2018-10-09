  ;; Boot sector that boots a C kernel in 32-bit protected mode
[org 0x7c00]
KERNEL_OFFSET equ 0x1000        ; kernel memory offset

  mov [BOOT_DRIVE], dl          ; BIOS stores boot drive in dl

  mov bp, 0x9000                ; stack
  mov sp, bp

  mov bx, MSG_REAL_MODE         ; display 16-bit real mode message
  call print
  call print_nl

  call load_kernel              ; load the kernel onto disk (disk_load.asm)

  call switch_pm                ; switch to 32-bit protected mode (protected_mode.asm)

  jmp $

  ;; routines
%include "boot/16bit_print.asm"
%include "boot/32bit_print.asm"
%include "boot/print_hex.asm"
%include "boot/gdt.asm"
%include "boot/disk_load.asm"
%include "boot/protected_mode.asm"

[bits 16]
load_kernel:
  mov bx, MSG_LOAD_KERNEL       ; display 'loading kernel' message
  call print
  call print_nl

  mov bx, KERNEL_OFFSET         ; set up paramters for disk_load routine
  mov dh, 15                    ; load first 15 sectors (excluding boot sector)
  mov dl, [BOOT_DRIVE]          ; to address KERNEL_OFFSET
  call disk_load                ; file: disk_load.asm
ret

  ;; arrive here after switching to 32-bit protected mode (protected_mode.asm)
[bits 32]
BEGIN_PM:
  mov ebx, MSG_PROT_MODE        ; display 32-bit protected mode message
  call print_pm

  call KERNEL_OFFSET            ; jump to address of loaded kernel code

  jmp $                         ; hang

  ;; global vars
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Enabled 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

  ;; bootsector padding
times 510-($-$$) db 0
dw 0xaa55
