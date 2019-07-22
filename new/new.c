
// dhruvil
// Sun 07 Jul 2019 12:02:10 PM IST
// new.c

#include "new.h"

// cls *x = New(&Cls, ...);
void *New(const void *_Class) {
    const Class *cls = _Class;
    void *obj = calloc(1, cls->size);

    assert(obj);
    *(const Class **)obj = cls;
    if (cls->ctor) {
        obj = cls->ctor(obj);
    }

    return obj;
}

// Delete(x);
void Delete(void *self) {
    const Class **cls = self;
    if (self && *cls && (*cls)->dtor) {
        self = (*cls)->dtor(self);
    }

    free(self);
    self = NULL;
}
