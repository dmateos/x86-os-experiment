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

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main() {
  //gdt_install();
  io_initialize();

  io_printf();
}
