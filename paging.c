#include "paging.h"
#include <stdint.h>

extern void loadPageDirectory(uint32_t*);
extern void enablePaging();

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void paging_setup(void)
{

    uint32_t i;
    for(i=0; i<1024; i++)
    {
        page_directory[i] = 0x00000002;
    }
 
    for(i = 0; i < 1024; i++)
    {
        first_page_table[i] = (i * 0x1000) | 3;
    }

    page_directory[0] = ((unsigned int)first_page_table) | 3;

    loadPageDirectory(page_directory);
    enablePaging();
}
