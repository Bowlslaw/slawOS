[bits 16]
  ;; Switch to protected mode
switch_pm:
  cli                           ; Must stop interrupts until prot mode interrupt vector is created

  lgdt [gdt_descriptor]         ; load global descriptor table

  mov eax, cr0                  ; to switch to prot mode, set first bit of cr0
  or eax, 0x1
  mov cr0, eax

  jmp CODE_SEG:init_pm          ; do far jump to 32-bit code, forcing CPU to flush cache
                                ; of pre-fetched, real-mode instructions

  [bits 32]
init_pm:                        ; set registers and stack
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov ebp, 0x9000
  mov esp, ebp

  call BEGIN_PM
