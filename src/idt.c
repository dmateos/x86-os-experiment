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

void idt_initialize() {

  io_printf("remapping irqs\n");
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  io_printf("installing idt table\n");
  idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
  idtp.base = (uint32_t)&idt;

  idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
  idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
  idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
  idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
  idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
  idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
  idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
  idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
  idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
  idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
  idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

  io_printf("installing irq table\n");
  idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
  idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
  idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
  idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
  idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
  idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
  idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
  idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
  idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
  idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
  idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
  idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
  idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
  idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
  idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
  idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

  idt_load();
}

void isr_handler(struct registers r) {
  switch(r.int_no) {
    case 0x03:
      io_printf("interrupt(%h) breakpoint exception, error: %h (%d)\n", r.int_no, r.err_code, r.err_code);
      break;
    case 0x04:
      io_printf("interrupt(%h) overflow exception, error: %h (%d)\n", r.int_no, r.err_code, r.err_code);
      break;
    case 0x08:
      io_printf("interrupt(%h) double fault, error: %h (%d)\n", r.int_no, r.err_code, r.err_code);
      break;
    case 0xd:
      io_printf("interrupt(%h) general protection fault, error: %h(%d) \n", r.int_no, r.err_code, r.err_code);
      break;
    default:
      io_printf("interurpt(%h) unhandled!!!, error: %h (%d)\n", r.int_no, r.err_code, r.err_code);
      break;
  }
}

isr_t interrupt_handlers[256];

void irq_handler(struct registers regs) {
  if(regs.int_no >= 40) {
    outb(0xa0, 0x20);
  }
  outb(0x20, 0x20);

  if(interrupt_handlers[regs.int_no] != 0) {
    isr_t handler = interrupt_handlers[regs.int_no];
    handler(regs);
  }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}
