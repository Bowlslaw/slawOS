  ;; Read sectors from boot disk using disk_read
  [org 0x7c00]

  mov [BOOT_DRIVE], dl          ; BIOS stores boot drive in dl

  mov bp, 0x8000                ; set stack safely out of way
  mov sp, bp

  mov bx, 0x9000                ; Load 5 sectors to 0x0000(ES):0x9000(BX)
  mov dh, 5
  mov dl, [BOOT_DRIVE]
  call disk_load

  mov dx, [0x9000]              ; print first loaded word, which should be 0xdada at addr 0x9000
  call print_hex
  call print_nl

  mov dx, [0x9000 + 512]        ; print first word from second loaded sector: 0xface
  call print_hex
  call print_nl

  jmp $

%include "print/print_string.asm"
%include "print/print_hex.asm"
%include "disk_load.asm"

BOOT_DRIVE: db 0

  times 510-($-$$) db 0
  dw 0xaa55

  times 256 dw 0xdada
  times 256 dw 0xface
