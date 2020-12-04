#include "string.h"
#include <stdarg.h>

size_t strlen(const char* str)
{
    size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void* memcpy(void* dest, const void * src, size_t size)
{
    if (dest==NULL || src==NULL)
        return NULL;
    unsigned int i;
    for (i=0;i<size;i++)
        *((char*)dest+i) = *((char*)src+i);
    return dest;
}

void* memset(void* dest, const int value, size_t size)
{
    unsigned int i;
    for (i=0;i<size;i++)
        ((char*)dest)[i] = value;
    return dest;
}

void* memchr(const void* ptr, int value, size_t num)
{
    unsigned int i;
    for (i=0;i<num;i++)
    {
        if ( ((char*)ptr)[i]==value )
            return ptr+i;
    }
    return NULL;
}

char* strcpy(char* dest, const char* src)
{
    if (dest==NULL || src==NULL)
        return NULL;
    return memcpy(dest,src,strlen(src)+1);
}

int strcmp(const char* first, const char* second)
{
    char f,s;
    while (true)
    {
        f = *(first++);
        s = *(second++);
        if (f=='\0' || s=='\0' || f!=s)
            return f-s;
    }
}

int strcmpwc(const char* first, const char* second)
{
    char f,s;
    while (true)
    {
        f = *(first++);
        s = *(second++);
        if (f=='\0' || s=='\0' || f==' ' || s==' ' || f!=s)
        {
            if (f==' ') f='\0';
            if (s==' ') s='\0';
            return f-s;
        }
    }
}

char* hexdump(char *dest, const void* data, size_t size)
{
    if (dest==NULL || data==NULL)
        return NULL;
    unsigned int i;
    unsigned char tleft, tright;
    unsigned char temp;
    for (i=0;i<size;i++)
    {
        temp = *((char*)data+i);
        tright = temp%16;
        tleft = temp/16;

        if (tright>=10) tright+=55;
        else tright+=48;
        if (tleft>=10) tleft+=55;
        else tleft+=48;

        *(dest+2*i) = tright;
        *(dest+2*i+1) = tleft;
    }
    //*(dest+2*i)='\0';
    dest[size*2]='\0';

    for(i=0;i<size;i++)
    {
        temp=dest[i];
        dest[i]=dest[2*size-i-1];
        dest[2*size-i-1]=temp;
    }


    return dest;
}

char* itoa(char *dest, long long int number)
{
    if (dest==NULL)
        return NULL;
    
    if (number==0)
    {
        dest[0]='0';
        dest[1]='\0';
        return dest;
    }


    int i;
    char c;
    char is_neg = number<0;
    if (is_neg)
        number=-number;

    for (i=0;number!=0;i++)
    {
        c = number%10;
        c+='0';
        number/=10;
        dest[i] = c;
    }
    if (is_neg)
    {
        dest[i]='-';
        i++;
    }
    dest[i]='\0';

    int j;
    for (j=0;j<i/2;j++)
    {
        c = dest[j];
        dest[j] = dest[i-j-1];
        dest[i-j-1] = c;
    }

    return dest;
}

int atoi(const char *src)
{
    int i;
    int value=0;
    int sign=1;
    for(i=0;;i++)
    {
        if (i==0 && src[0] == '-')
        {
            sign=-1;
            continue;
        }
        if ('0'<=src[i]&&src[i]<='9')
        {
            value*=10;
            value+=src[i]-'0';
        }
        else
        {
            return value*sign;
        }
    }
}

int printf(char *format, ...)
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
                    terminal_writestring(intstring);
                    written+= strlen(intstring);
                break;

                case 'h':
                    hexdump(intstring,va_arg(vl,int),1);
                    terminal_writestring(intstring);
                    written+= strlen(intstring);
                break;
                case 'H':
                    hexdump(intstring,va_arg(vl,int),4);
                    terminal_writestring(intstring);
                    written+= strlen(intstring);
                break;

                case 's':
                    stringtemp = va_arg(vl,char*); 
                    terminal_writestring(stringtemp);
                    written+= strlen(stringtemp);
                break;

                case 'c':
                    terminal_putchar(va_arg(vl,int));
                    written++;
                break;
                
                case '%':
                    terminal_putchar('%');
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
            terminal_putchar(format[0]);
            format++;
            written++;
        }
    }

    va_end(vl);
    return 0;
}