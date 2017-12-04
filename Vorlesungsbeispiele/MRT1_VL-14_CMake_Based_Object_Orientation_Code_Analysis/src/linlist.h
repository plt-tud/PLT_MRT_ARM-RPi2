#ifndef HAVE_LINLIST_H
#define HAVE_LINLIST_H

#include <stdint.h>
#include "cobj.h"
#include "linlist_elem.h"

typedef struct linlist_t {
    cobj obj_fp;
    linlist_elem *first;
} linlist;

linlist *linlist_new();
void linlist_init(linlist *this);
void linlist_delete(linlist *this);
void linlist_deleteMembers(linlist *this);

int32_t linlist_appendElement(linlist *this, cobj *payload);
cobj *linlist_removeElement(linlist *this, cobj *payload);

#endif /* HAVE_LINLIST_H */
