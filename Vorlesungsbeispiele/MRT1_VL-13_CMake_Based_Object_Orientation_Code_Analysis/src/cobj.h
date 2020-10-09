#ifndef HAVE_COBJ_H
#define HAVE_COBJ_H

typedef struct cobj_t cobj;

typedef void  (*cobj_delete_fp)(cobj* this);
typedef void  (*cobj_deleteMembers_fp)(cobj* this);

typedef struct cobj_t {
    cobj_delete_fp delete;
    cobj_deleteMembers_fp deleteMembers;
} cobj;

#endif
