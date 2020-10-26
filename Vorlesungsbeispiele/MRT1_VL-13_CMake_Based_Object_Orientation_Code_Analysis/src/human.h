
#ifndef HAVE_HUMAN_H
#define HAVE_HUMAN_H

#include "mamal.h"

typedef struct human_t {
    mamal mamalAttr;
    char *name;
} human;

human* human_new(const char* name);
void human_init(human *this, const char* name);
void human_delete(human *this);
void human_deleteMembers(human *this);

void human_makeSound(human *this);

#endif /* HAVE_HUMAN_H */
