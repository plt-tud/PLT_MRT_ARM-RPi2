#ifndef HAVE_MAMAL_H
#define HAVE_MAMAL_H

#include <stdint.h>
#include "cobj.h"

typedef void (*mamal_makeSound_f)();

typedef struct mamal_t {
    cobj obj_fp;
    char *genus;
    char *species;
    uint16_t age;
    mamal_makeSound_f mamal_makeSound;
} mamal;

mamal* mamal_new();
void mamal_init(mamal *this);
void mamal_delete(mamal *this);
void mamal_deleteMembers(mamal *this);

void mamal_makeSound_default(mamal *this);

#endif
