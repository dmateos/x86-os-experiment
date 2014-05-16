#include <io.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void io_initialize() {
  size_t x,y;
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = COLOR_WHITE | COLOR_BLACK << 4;
  terminal_buffer = (uint16_t*) 0xB8000;

  for(y = 0; y < VGA_HEIGHT; y++) {
    for(x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[y * VGA_WIDTH + x] = ((uint16_t)' ') | ((uint16_t)terminal_color) << 8;
    }
  }
}

void io_putc(char c) {
  if(c == '\n') {
    terminal_row++;
    terminal_column = 0;
  } else {
    terminal_buffer[terminal_column * VGA_WIDTH + terminal_row] = ((uint16_t)c) | ((uint16_t)terminal_color) << 8;
    if(++terminal_column == VGA_WIDTH) {
      terminal_column = 0;
      if(++terminal_row == VGA_HEIGHT) {
        terminal_row = 0;
      }
    }
  }
}

void io_printf(const char *s, ...) {
  io_putc('t');
  io_putc('e');
  io_putc('s');
  io_putc('t');
  io_putc('\n');
}
