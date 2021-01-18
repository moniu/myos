#include "serial.h"


#define PORT 0x3f8

void init_serial() 
{
   outportb(PORT + 1, 0x00);    // Disable all interrupts
   outportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outportb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outportb(PORT + 1, 0x00);    //                  (hi byte)
   outportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outportb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outportb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

void print_serial(char* s)
{
   int size = strlen(s);
   int i;
   for(i=0;i<size;i++)
   {
      write_serial(s[i]);
   }
}

int serial_printf(char *format, ...)
{
   va_list vl;
    va_start(vl,format);

    char intstring[22]; // temp do konwersji inta na stringa
    char* stringtemp;
    int written = 0;

    while(format[0]!='\0')
    {
        if (format[0] == '%')
        {
            switch(format[1])
            {
                case 'd':
                    itoa(intstring,va_arg(vl,int));
                    print_serial(intstring);
                    written+= strlen(intstring);
                break;

                case 'h':
                    hexdump(intstring,(void*)va_arg(vl,int),1);
                    print_serial(intstring);
                    written+= strlen(intstring);
                break;
                case 'H':
                    hexdump(intstring,(void*)va_arg(vl,int),4);
                    print_serial(intstring);
                    written+= strlen(intstring);
                break;

                case 's':
                    stringtemp = va_arg(vl,char*); 
                    print_serial(stringtemp);
                    written+= strlen(stringtemp);
                break;

                case 'c':
                    write_serial(va_arg(vl,int));
                    written++;
                break;
                
                case '%':
                    write_serial('%');
                    written++;
                break;

                default:
                    va_end(vl);
                    return -1;
            }
            format+=2;
        }
        else
        {
            write_serial(format[0]);
            format++;
            written++;
        }
    }

    va_end(vl);
    return 0;
}

int is_transmit_empty() 
{
   return inportb(PORT + 5) & 0x20;
}
 
void write_serial(char a)
{
   while (is_transmit_empty() == 0);
 
   outportb(PORT,a);
}