#include "../src/llist.h"

// For testing purposes!!
static void free_static_cells(struct list *lst) {
	struct cell *cur;
	struct cell *tmp;
    // Uninitialized list 
	if (lst == NULL) { 
        error_msg("Uninitialized list pointer.");
    }
    // Free each cell one by one
	cur = lst->head;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
        // Statically allocated!!
        // free(tmp->fname);
        // free(tmp->lname);
        // free(tmp->zip);
		free(tmp);
	}
	lst->head = NULL;
}

void free_static_list(struct list* lst) {
    free_static_cells(lst);
	free(lst);
}

int main() {
    // Tests the dirty way but also to test with valgrind!

    // 1. make_cell
    // struct cell* c;
    // c = make_cell("Quentin", "DUCASSE", "59800");
    // free(c);
    // return 0;

    // 1. push
    // struct list* lst;
    // struct cell* c1; 
    // struct cell* c2;
    // lst = new_list();
    // c1 = make_cell("Quentin", "DUCASSE", "59800");
    // c2 = make_cell("Quentin", "AUCASSE", "59800");
    // push(lst, c1);
    // push(lst, c2);
    // free_static_list(lst);
    // return 0;

    // 1. pop

    // 2. make_cell_from_line

    // 2. load_file

    // 2. compare_cells

    // 2. insert

    // 3.1 new_llist/free_llist

    // 3.2 print_lcell

    // 3.3 print_llist

    // 3.4 make_lcell(_from_line)

    // 3.5 lload_file

    // 3.6 linsert

<<<<<<< HEAD
    return 0;
}
=======
static MunitResult test_insert_null_list(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_insert_empty_list(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_insert_first(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_insert_middle(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_insert_last(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

/* Test Suite
========== */

static MunitTest test_suite_tests[] = {
    {(char*) "/print/cell/null",  test_smoke_print_cell_null,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/cell/empty", test_smoke_print_cell_empty,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/cell/full",  test_smoke_print_cell_full,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/list/null",  test_smoke_print_list_null,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/list/empty", test_smoke_print_list_empty,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/list/full",  test_smoke_print_list_full,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/make/cell/values", test_make_cell_from_values,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/make/cell/line",   test_make_cell_from_line,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/gt",       test_compare_cells_lname_gt,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/lt",       test_compare_cells_lname_lt,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/eqgt",     test_compare_cells_lname_eq_fname_gt,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/eqlt",     test_compare_cells_lname_eq_fname_lt,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/null",      test_insert_null_list,                 NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/empty",     test_insert_empty_list,                NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/first",     test_insert_first,                     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/middle",    test_insert_middle,                    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/last",      test_insert_last,                      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite test_suite = { 
    (char*) "", 
    test_suite_tests, 
    NULL, 
    1, 
    MUNIT_SUITE_OPTION_NONE 
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, (void*) "munit", argc, argv);
}
>>>>>>> 628f55bffc1c989e5278053af5249069bb09c04a
