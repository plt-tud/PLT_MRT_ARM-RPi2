
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include "debugMsg.h"

dog* dog_new(const char* name, human *owner) {
    dog *this = (dog *) malloc(sizeof(dog));
    dog_init(this, name, owner);
    
    return this;
}

void dog_init(dog *this, const char* name, human *owner) {
    mamal_init((mamal*) this);
    this->mamalAttr.obj_fp.delete = dog_delete;
    this->mamalAttr.obj_fp.deleteMembers = dog_deleteMembers;
    this->mamalAttr.mamal_makeSound = dog_makeSound;
    
    this->mamalAttr.genus = (char *) malloc(strlen("Canis")+1);
    strcpy(this->mamalAttr.genus, "Canis");
    this->mamalAttr.species = (char *) malloc(strlen("Canis Familaris")+1);
    strcpy(this->mamalAttr.species, "Canis Familaris");
    
    this->name = (char *) malloc(strlen(name));
    strcpy(this->name, name);
    
    this->owner = owner;
    return;
}

void dog_delete(dog *this) {
    if(this) {
        dog_deleteMembers(this);
        free(this);
        DEBUG("Dog was deallocated");
    }
    return;
}

void dog_deleteMembers(dog *this) {
    if(this->name) {
        free(this->name);
        this->name = NULL;
    }
    // unlink owner, don't delete
    this->owner = NULL;
    
    mamal_deleteMembers((mamal*) this);
    return;
}

void dog_makeSound(dog *this) {
    if(this) {
        printf("%s (%s,%s) says 'Wuff? Wuff!' (translated: '%s, play?!')\n", this->name, this->mamalAttr.genus, this->mamalAttr.species, this->owner->name);
    }
    return;
}
