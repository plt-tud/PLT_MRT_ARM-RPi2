#include <check.h>
#include "mamal.h" 
#include "linlist.h" 

START_TEST(test_linListAddEmpty) {
  linlist *l = linlist_new();
  mamal *m0 = mamal_new();
  
  linlist_appendElement(l, (cobj *) m0);
  ck_assert_int_eq(l->first->payload, m0);
  ck_assert_int_eq(l->first->next, 0);
  
  linlist_delete(l);
  ck_assert_int_eq(l->first, 0);
} END_TEST

void main() {
  
  return;
}
