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

void kernel_main() {
  io_initialize();
  gdt_initialize();
  idt_initialize();

  asm volatile ("int $0x3");
  asm volatile ("int $0x4");

  while(true) {
  }
}
