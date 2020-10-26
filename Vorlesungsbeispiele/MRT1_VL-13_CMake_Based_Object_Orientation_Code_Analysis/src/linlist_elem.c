#include "debugMsg.h"

#include "linlist.h"
#include <stdlib.h>

linlist_elem* linlist_elem_new(cobj *payload) {
    linlist_elem* this = (linlist_elem*) malloc(sizeof(linlist_elem));
    linlist_elem_init(this, payload);
    return this;
}

void linlist_elem_init(linlist_elem *this, cobj *payload) {
    this->obj_fp.delete = linlist_elem_delete;
    this->obj_fp.deleteMembers = linlist_elem_deleteMembers;
    
    this->next = NULL;
    this->payload = payload;
    return;
}

void linlist_elem_deleteMembers(linlist_elem *this) {
    // Do not delete the payload or next elements
    return;
}

void linlist_elem_delete(linlist_elem *this) {
    if(this) {
        if(this->payload) {
            this->payload->delete(this->payload);
            this->payload = NULL;
        }
        free(this);
    }
    DEBUG("List element was deallocated");
    return;
}

int32_t linlist_elem_appendElement(linlist_elem *list, cobj *payload) {
    if(list == NULL)
        return -1;
    
    linlist_elem *current = list;
    int index = 0;
    while(current->next != NULL) {
        current = current->next;
        index++;
    }
    
    current->next = linlist_elem_new(payload);
    return index;
}

cobj *linlist_elem_removeElement(linlist_elem *list, cobj *payload) {
    if(list == NULL)
        return NULL;
    
    linlist_elem *current = list;
    linlist_elem *previous = NULL;
    
    while(current != NULL) {
        if(current->payload == payload) {
            if(previous != NULL)
                previous->next = current->next; //Unlink current from list
            void *ptr = current->payload;
            linlist_elem_delete(current);
            return ptr;
        }
        previous = current;
        current = current->next;
    }
    
    return NULL;
}
