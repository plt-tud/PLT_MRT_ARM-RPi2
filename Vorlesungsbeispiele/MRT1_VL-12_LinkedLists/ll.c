#include <stdio.h>
#include <stdlib.h>

typedef struct linListElem_t {
	void* payload;
	struct linListElem_t *next;
} linListElem;

linListElem* ll_new(void* payload) {
	linListElem* llp;
	llp = (linListElem *) malloc(sizeof(linListElem));
	if (llp != NULL) {
		llp->payload = payload;
		llp->next = NULL;
	}
	return llp;
}

linListElem* ll_append(linListElem* first, linListElem* next) {
	linListElem* c = first;
	while (c->next != NULL) { // travers to last element 
		c = c->next;
	}
	c->next = next;
}
void ll_dump(linListElem* first) {
	printf("%x : %i\n", first, first->payload);
	if (first->next != NULL) ll_dump(first->next);
}

main() {
	linListElem *first = ll_new((void*) 42);
	ll_append(first, ll_new((void*) 47));
	ll_append(first, ll_new((void*) 11));
	ll_dump(first);
}
 
