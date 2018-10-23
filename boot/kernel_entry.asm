global _start:
  ;; Ensure jump into kernel's entry function
[bits 32]

_start:
  [extern kmain]                   ; reference external symbol 'kmain' from kernel.c
  call kmain                       ; invoke kmain() in kernel.c
  jmp $                            ; hang
