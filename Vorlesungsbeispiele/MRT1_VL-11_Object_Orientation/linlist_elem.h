#ifndef HAVE_LINLIST_ELEM_H
#define HAVE_LINLIST_ELEM_H

#include <stdint.h>
#include "cobj.h"

typedef struct linlist_elem_t {
    cobj obj_fp;
    cobj *payload;
    struct linlist_elem_t *next;
} linlist_elem;

/**
 * @brief creates a new list element
 * 
 * @param payload p_payload: to be assigned to the new list element
 * @return linlist_elem* allocated element
 */
linlist_elem* linlist_elem_new(cobj *payload);


/**
 * @brief initializes a new list element
 * 
 * @param this p_this: element to be initialized
 * @param payload p_payload: to be assigned to the new list element
 */
void linlist_elem_init(linlist_elem *this, cobj *payload);

void linlist_elem_deleteMembers(linlist_elem *this);

/**
 * @brief deletes a specific list element
 * 
 * @param this element to delete
 */
void linlist_elem_delete(linlist_elem *this);


/**
 * @brief Adds the payload to the end of list
 * 
 * @param list A pointer to a list element in the list (preferrably the first element)
 * @param payload Pointer to any type
 * @return int32_t, Positive index where the element was added on success, negative value on error
 */
int32_t linlist_elem_appendElement(linlist_elem *list, cobj *payload);


/**
* @brief Removes the first element containing payload from the list
 * 
 * @param list A pointer to a list element in the list (preferrably the first element)
 * @param payload Pointer to any type
 * @return void: payload of the removed element
 */
cobj *linlist_elem_removeElement(linlist_elem *list, cobj *payload);

#endif /* HAVE_LINLIST_ELEM_H */
