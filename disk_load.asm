  ;; load DH sectors into ES:BX from drive DL
disk_load:
  push dx                       ; store dx on stack so we can later recall how many
                                ; sectors were requested
  mov ah, 0x02                  ; BIOS read sector function
  mov al, dh                    ; read BH sectors
  mov ch, 0x00                  ; cylinder 0
  mov dh, 0x00                  ; head 0
  mov cl, 0x02                  ; sector 2 (after boot sector)
  int 0x13                      ; BIOS interrupt

  jc disk_error                 ; jump if error (carry flag set)

  pop dx                        ; restore dx from stack
  cmp dh, al                    ; al = sectors read, dh = sectors expected
  jne disk_error
ret

disk_error:
  mov bx, DISK_ERROR_MSG
  call print_string
  jmp $

  ;; Variables
  DISK_ERROR_MSG db "Disk read error!", 0
