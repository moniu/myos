#ifndef SERIAL_H
#define SERIAL_H 

#include "port.h"
#include "string.h"

void init_serial();
void print_serial(char* s);
int is_transmit_empty();
void write_serial(char a);
int serial_printf(char *format, ...);

#endif