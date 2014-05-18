#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "wah"
#endif

#if !defined(__i386__)
#error "wah"
#endif

#include "io.h"
#include "gdt.h"
#include "idt.h"

void kernel_main() {
  io_initialize();

  gdt_initialize();
  idt_install();

  io_printf("hello world!! %d\n", strlen("hello world!"));
  io_printf("hello world!! %h\n", strlen("hello world!"));
  while(true) {
  }
}
