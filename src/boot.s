.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

#Setup a stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
# Our linker script jumps to start
.global _start
.type _start, @function
_start:
  movl $stack_top, %esp
  call kernel_main
  cli
  hlt
.Lhang:
  jmp .Lhang

# Function to flush the GDT table once we setup the data as required
# in C
.global gdt_flush
gdt_flush:
  lgdtl gp
  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  ljmp $0x08, $next
next:
  ret

# Function to flush the IDT table once we setup the data as required
# in C
.global idt_load
idt_load:
  lidt idtp
  ret

# These two macros help us setup the interupt tables
.macro isr_errorcode num=0
  .global isr\num
  isr\num:
    cli
    push \num
    jmp isr_common_stub
.endm

.macro isr_noerrorcode num=0
  .global isr\num
  isr\num:
    cli
    push 0
    push \num
    jmp isr_common_stub
.endm

# Use the above macros to generate a bunch of isr methods, one for each
# interrupt
isr_noerrorcode 0
isr_noerrorcode 1
isr_noerrorcode 2
isr_noerrorcode 3
isr_noerrorcode 4
isr_noerrorcode 5
isr_noerrorcode 6
isr_noerrorcode 7
isr_errorcode 8
isr_noerrorcode 9
isr_errorcode 10
isr_errorcode 11
isr_errorcode 12
isr_errorcode 13
isr_errorcode 14
isr_noerrorcode 15
isr_noerrorcode 16
isr_noerrorcode 17
isr_noerrorcode 18
isr_noerrorcode 19
isr_noerrorcode 20
isr_noerrorcode 21
isr_noerrorcode 22
isr_noerrorcode 23
isr_noerrorcode 24
isr_noerrorcode 25
isr_noerrorcode 26
isr_noerrorcode 27
isr_noerrorcode 28
isr_noerrorcode 29
isr_noerrorcode 30
isr_noerrorcode 31

# The above interupt methods call this method which sets up state and calls our 
# handler which is also defined in C
isr_common_stub:
  pusha           # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
  movw %ax, %ds    # Lower 16-bits of eax = ds.
  push %eax       # Save the data segment descriptor

  movw $0x10, %ax  # load the kernel data segment descriptor
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  call isr_handler

  pop %eax        # reload the original data segment descriptor
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  popa            # Pops edi,esi,ebp...
  add 8, %esp     # Cleans up the pushed error code and pushed ISR number
  sti
  iret            # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP


