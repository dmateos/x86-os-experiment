#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idtp;


void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_low = (base & 0xFFFF);
  idt[num].base_high = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags;
}

extern void idt_load();

void idt_install() {
  idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
  idtp.base = (unsigned int)&idt;
  
  idt_load();
}
