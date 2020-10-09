#include <stdlib.h>
#include <stdio.h>
#include "mamal.h"

#include "debugMsg.h"

mamal* mamal_new() {
    mamal *this = (mamal*) malloc(sizeof(mamal));
    mamal_init(this);
    return this;
}

void mamal_init(mamal *this) {
    this->obj_fp.delete = mamal_delete;
    this->obj_fp.deleteMembers = mamal_deleteMembers;
    this->mamal_makeSound = mamal_makeSound_default;
    
    this->genus  = NULL;
    this->species = NULL;
    this->age = 0;
    return;
}

void mamal_delete(mamal *this) {
    if(this) {
        mamal_deleteMembers(this);
        free(this);
    }
    DEBUG("Mamal was deallocated");
    return;
}

void mamal_deleteMembers(mamal *this) {
    if(this->genus)
        free(this->genus);
    if(this->species)
        free(this->species);
    return;
}

void mamal_makeSound_default(mamal *this) {
    printf("Generic mamal makes no sound\n");
    return;
}

