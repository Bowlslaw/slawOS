  ;; GDT
gdt_start:

gdt_null:                       ; mandatory null descriptor
  dd 0x0
  dd 0x0

gdt_code:                       ; code segment descriptor
  ;; base=0x0, limit=0xfffff
  ;; 1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001b
  ;; type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
  ;; 2nd flags: (granularity)1 (32-it default)1 (64-bit seg)0 (AVL)0 -> 1100b
  dw 0xffff                     ; limit (0-15)
  dw 0x0                        ; base (0-15)
  db 0x0                        ; base (16-23)
  db 10011010b                  ; 1st flags, type flags
  db 11001111b                  ; 2nd flags, limit (16-32)
  db 0x0                        ; base (24-31)

gdt_data:                       ; data segment descriptor
  ;; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
  dw 0xffff
  dw 0x0
  db 0x0
  db 10010010b                  ; 1st flags, type flags
  db 11001111b                  ; 2nd flags, limit
  db 0x0

gdt_end:                        ; assembler can calculate size of GDT for GDT descriptor
gdt_descriptor:
  dw gdt_end - gdt_start - 1    ; Size of GDT, always less one of the true size
  dd gdt_start                  ; start addr of GDT

  CODE_SEG equ gdt_code - gdt_start
  DATA_SEG equ gdt_data - gdt_start
