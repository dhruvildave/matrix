
// dhruvil
// Sun 07 Jul 2019 12:02:10 PM IST
// new.h

#if !defined(_NEW_H)
#define _NEW_H 1

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Class_ {
    size_t size;
    void *(*ctor)(void *self);
    void *(*dtor)(void *self);
} Class;

// cls *x = New(&Cls);
void *New(const void *_class);

// Delete(x);
void Delete(void *self);

#endif // _NEW_H
