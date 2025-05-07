#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef enum {
    ALLOC,
    FREE
} e_action;

typedef struct s_garbage{
    void *ptr;
    struct s_garbage *next;
}   t_garbage;

void *alloc(size_t size, e_action action);

#endif