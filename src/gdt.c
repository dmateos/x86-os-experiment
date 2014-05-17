#include "gdt.h"

struct gdt_entry gdt[3];
struct gdt_ptr gp;

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;

  io_printf("gdt set gate\n");
}

void gdt_install() {
  io_printf("installing gdt table\n");

  gp.limit = (sizeof(struct gdt_entry) * 3) -1;
  gp.base = (unsigned int)&gdt;

  gdt_set_gate(0, 0, 0, 0, 0);
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  /* load the gdtr registry */
  asm("lgdtl (gp)");

  /* initiliaz the segments */
  asm("   movw $0x10, %ax    \n \
          movw %ax, %ds    \n \
          movw %ax, %es    \n \
          movw %ax, %fs    \n \
          movw %ax, %gs    \n \
          ljmp $0x08, $next    \n \
          next:        \n");
}
