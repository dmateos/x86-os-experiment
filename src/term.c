/* Hardware text mode color constants. */
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
  size_t x,y;
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  for ( y = 0; y < VGA_HEIGHT; y++ ) {
    for ( x = 0; x < VGA_WIDTH; x++ ) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = make_vgaentry(' ', terminal_color);i
    }
  }
}

void terminal_setcolor(uint8_t color) {
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {
  if(c == '\n') {
    ++terminal_row;
    terminal_column = 0;
  }
  else {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

    if ( ++terminal_column == VGA_WIDTH ) {
      terminal_column = 0;
      if ( ++terminal_row == VGA_HEIGHT ) {
        terminal_row = 0;
      }
    }
  }
}

void terminal_writestring(const char* data) {
  size_t datalen = strlen(data);
  size_t i;
  for ( i = 0; i < datalen; i++ )
    terminal_putchar(data[i]);
}
