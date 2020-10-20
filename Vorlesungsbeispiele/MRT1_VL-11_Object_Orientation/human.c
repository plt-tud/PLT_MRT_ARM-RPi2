#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "human.h"
#include "debugMsg.h"

human* human_new(const char* name) {
    human *this = (human *) malloc(sizeof(human));
    human_init(this, name);
    
    return this;
}

void human_init(human *this, const char* name) {
    mamal_init((mamal*) this);
    this->mamalAttr.obj_fp.delete = human_delete;
    this->mamalAttr.obj_fp.deleteMembers = human_deleteMembers;
    this->mamalAttr.mamal_makeSound = human_makeSound;
    
    this->mamalAttr.genus = (char *) malloc(strlen("Homo")+1);
    strcpy(this->mamalAttr.genus, "Homo");
    this->mamalAttr.species = (char *) malloc(strlen("Homo Sapiens")+1);
    strcpy(this->mamalAttr.species, "Homo Sapiens");
    
    this->name = (char *) malloc(strlen(name) + 1);
    strcpy(this->name, name);
    
    return;
}

void human_delete(human *this) {
    if(this) {
        human_deleteMembers(this);
        free(this);
        DEBUG("Human was deallocated");
    }
    return;
}

void human_deleteMembers(human *this) {
    if(this->name) {
        free(this->name);
        this->name = NULL;
    }
    this->name = NULL;
    
    mamal_deleteMembers((mamal*) this);
    return;
}

void human_makeSound(human *this) {
    if(this) {
        printf("%s (%s,%s) says 'Hi there'\n", this->name, this->mamalAttr.genus, this->mamalAttr.species);
    }
    return;
}
