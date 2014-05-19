#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "use a cross compiler"
#endif

#if !defined(__i386__)
#error "this is a 32bit kernel atm"
#endif

#include "io.h"
#include "gdt.h"
#include "idt.h"

uint32_t tick;

static void timer_cb(struct registers r) {
  tick++;
  io_printf("tick %d\n", tick);
}

void init_timer(uint32_t freq) {
  register_interrupt_handler(32, &timer_cb);
  uint32_t div = 1193180 / freq;
  outb(0x43, 0x36);
  uint8_t l = (uint8_t)(div & 0xFF);
  uint8_t h = (uint8_t)( (div>>8) & 0xFF );
  outb(0x40, l);
  outb(0x40, h);
  io_printf("timer init\n");
}

void kernel_main() {
  io_initialize();
  gdt_initialize();
  idt_initialize();
  
  asm volatile ("int $0x3");
  asm volatile ("int $0x3");
  asm volatile ("int $0x4");

  io_printf("hello world\n");

  init_timer(5000);

  while(true) {

  }
}
