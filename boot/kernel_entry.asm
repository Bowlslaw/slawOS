  ;; Ensure jump into kernel's entry function
[bits 32]
[extern main]                   ; reference external symbol 'main' from kernel.c
call main                       ; invoke main() in kernel.c
jmp $                           ; hang
