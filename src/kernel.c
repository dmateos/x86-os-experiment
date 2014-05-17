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

void gdt_install();

void kernel_main() {
  io_initialize();
  gdt_install();

  io_printf("hello world!! %d %d\n", 1337, 1338);
  while(true) {
  }
}
