#ifndef HAVE_DOG_H
#define HAVE_DOG_H

#include "mamal.h"
#include "human.h"

typedef struct human_t human;

typedef struct dog_t {
    mamal mamalAttr;
    char *name;
    human *owner;
} dog;

dog* dog_new(const char* name, human *owner);
void dog_init(dog *this, const char* name, human *owner);
void dog_delete(dog *this);
void dog_deleteMembers(dog *this);

void dog_makeSound(dog *this);

#endif
