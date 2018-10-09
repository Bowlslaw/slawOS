print_hex:
  pusha

  mov cx, 0                     ; index

hex_loop:
  cmp cx, 4                     ; loop 4 times
  je end

  ;; convert last char of dx to ascii
  mov ax, dx
  and ax, 0x000f                ; bitmask
  add al, 0x30                  ; convert to ascii
  cmp al, 0x39
  jle step2
  add al, 7

step2:
  ;; get correct position of string
  ;; bx <- base addr + str len - char index
  mov bx, HEX_OUT + 5           ; base + length
  sub bx, cx                    ; index
  mov [bx], al
  ror dx, 4

  add cx, 1
  jmp hex_loop

end:
  mov bx, HEX_OUT
  call print_string

  popa
ret

HEX_OUT:
  db '0x0000', 0
