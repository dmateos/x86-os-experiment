#include "gdt.h"

struct gdt_entry gdt[5];
struct gdt_ptr gp;

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;

  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;

  io_printf("gdt set gate\n");
}

extern void gdt_flush();

void gdt_initialize() {
  io_printf("installing gdt table\n");

  gp.limit = (sizeof(struct gdt_entry) * 5) -1;
  gp.base = (unsigned int)&gdt;

  gdt_set_gate(0, 0, 0, 0, 0);                  // null
  gdt_set_gate(1, 0x0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code
  gdt_set_gate(2, 0x0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data
  gdt_set_gate(3, 0x0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code
  gdt_set_gate(4, 0x0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data

  gdt_flush();
}
