#include <check.h>
#include <stdlib.h>
#include "mamal.h" 
#include "linlist.h" 

/* Individual Tests */
START_TEST(test_linListAddEmpty) {
    linlist *l = linlist_new();
    mamal *m0 = mamal_new();
    
    linlist_appendElement(l, (cobj *) m0);
    ck_assert_int_eq(l->first->payload, m0);
    ck_assert_int_eq(l->first->next, 0);
    
    linlist_delete(l);
    ck_assert_int_eq(l->first, 0);
} END_TEST

/* Test suites (bundle testcases) */
Suite *build_linlist_suite(void) {
    Suite *s;
    s = suite_create("Test linear list operations");
    
    TCase *tc_linlists = tcase_create("LinList Testcases");
    tcase_add_test(tc_linlists, test_linListAddEmpty); 
    
    suite_add_tcase(s, tc_linlists);
    return s;
}

/* Test Suite Runner, Output wrapper*/
int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    s  = build_linlist_suite();
    sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
