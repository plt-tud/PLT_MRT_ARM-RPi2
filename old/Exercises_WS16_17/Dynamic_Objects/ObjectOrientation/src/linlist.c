#include <stdlib.h>
#include "debugMsg.h"
#include "linlist.h"

linlist *linlist_new() {
    linlist *this = (linlist *) malloc(sizeof(linlist));
    linlist_init(this);
    return this;
}

void linlist_init(linlist *this) {
    this->obj_fp.delete = linlist_delete;
    this->obj_fp.deleteMembers = linlist_deleteMembers;
    
    this->first = NULL;
    return;
}

void linlist_delete(linlist *this) {
    if(this) {
        linlist_deleteMembers(this);
        free(this);
    }
    return;
}

void linlist_deleteMembers(linlist *this) {
    linlist_elem *current;
    while(this->first != NULL) {
        current = this->first;
        this->first = this->first->next;
        linlist_elem_delete(current);
    }
    return;
}

int32_t linlist_appendElement(linlist *this, cobj *payload) {
    DEBUG("Adding new list element");
    if(this->first == NULL) {
        this->first = linlist_elem_new(payload);
        return 0;
    }
    return linlist_elem_appendElement(this->first, payload);
}

cobj *linlist_removeElement(linlist *this, cobj *payload) {
    return linlist_elem_removeElement(this->first, payload);
}
