.globl gdt_flush
gdt_flush:
  movl 4(%esp), %eax    /* load argument */
  lgdt (%eax)           /* Set GDT */

  movw $16, %ax         /* Get GDT[2] (each entry is 8 bytes)*/
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movw %ax, %ss

  jmpl $0x08, $complete_flush /* reload CS with far jump */

complete_flush:
  ret
