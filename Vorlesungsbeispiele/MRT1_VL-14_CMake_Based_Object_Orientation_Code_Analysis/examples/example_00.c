#include <stdio.h>

#include "linlist.h"
#include "mamal.h"
#include "human.h"
#include "dog.h"

int main() {
    linlist mamalList;
    linlist_init(&mamalList);
    
    human *tom = human_new("Tom");
    dog *bello = dog_new("Bello", tom);
    
    linlist_appendElement(&mamalList, (cobj *) mamal_new());
    linlist_appendElement(&mamalList, (cobj *) tom);
    linlist_appendElement(&mamalList, (cobj *) bello);
    
    linlist_elem *current = mamalList.first;
    while(current != NULL) {
        ((mamal *) current->payload)->mamal_makeSound((mamal *) current->payload);
        current = current->next;
    }
    
    linlist_deleteMembers(&mamalList);
    return 0;
}
