#include "io.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void io_initialize() {
  size_t x,y;
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = COLOR_LIGHT_GREY | COLOR_BLACK << 4;
  terminal_buffer = (uint16_t*) 0xB8000;

  for(y = 0; y < VGA_HEIGHT; y++) {
    for(x = 0; x < VGA_WIDTH; x++) {
      terminal_buffer[y * VGA_WIDTH + x] = ((uint16_t)' ') | ((uint16_t)terminal_color) << 8;
    }
  }
}

void io_putc(char c) {
  if(c == '\n') {
    terminal_row++;
    terminal_column = 0;
  } else if(c == '\r') {
    terminal_column = 0;
  } else {
    terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = ((uint16_t)c) | ((uint16_t)terminal_color) << 8;
    if(++terminal_column == VGA_WIDTH) {
      terminal_column = 0;
      if(++terminal_row == VGA_HEIGHT) {
        terminal_row = 0;
      }
    }
  }
}

void io_printf(const char *s, ...) {
  int ival;
  char ibuf[32];
  va_list args;
  va_start(args, *s);

  while(*s != '\0') {
    if(*s == '%') {
      s++;
     switch(*s) {
      case 'd':
        ival = va_arg(args, int);
        itoa(ival, ibuf, 10);
        io_printf(ibuf);
        break;
      case 'h':
        ival = va_arg(args, int);
        itoa(ival, ibuf, 16);
        io_printf("0x");
        io_printf(ibuf);
        break;
     }
    } else {
      io_putc(*s);
    }
    s++;
  }
}

void outb(uint16_t port, uint8_t value) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

uint16_t inw(uint16_t port) {
  uint16_t ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

