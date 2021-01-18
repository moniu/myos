#ifndef MUTEX_H
#define MUTEX_H 


struct mutex_t
{
    unsigned int serving;
    unsigned int next;
};

void mutex_get(struct mutex_t *mutex);
void mutex_free(struct mutex_t *mutex);

#endif