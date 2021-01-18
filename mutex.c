#include "mutex.h"

void mutex_get(struct mutex_t *mutex)
{
    unsigned int recieved = ++mutex->next;
    while(mutex->serving!=recieved)
    {
        asm("pause");
    }
}
void mutex_free(struct mutex_t *mutex)
{
    mutex->serving++;
}