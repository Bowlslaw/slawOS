  ;; 32-bit protected mode printing routine
  ;; only works in 32-bit procected mode
[bits 32]
VIDEO_MEMORY equ 0xb8000        ; VGA memory starts here
WHITE_ON_BLACK equ 0x0f         ; code for 'white on black'

  ;; print null-terminated string point to by edx
print_pm:
  pusha
  mov edx, VIDEO_MEMORY         ; set edx to start of video memory

print_pm_loop:
  mov al, [ebx]                 ; store char at ebx in al
  mov ah, WHITE_ON_BLACK        ; store attributes in AH

  cmp al, 0                     ; if(al == 0), end string
  je print_pm_loop_done

  mov [edx], ax                  ; store char and attributes at current character call
  add ebx, 1                    ; increment ebx to next char in string
  add edx, 2                    ; mov to next char in vid mem

  jmp print_pm_loop

print_pm_loop_done:
  popa
ret
