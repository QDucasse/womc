#include <stdlib.h>
#include "munit/munit.h"
#include "../src/llist.h"

/* Cell making
=========== */

static MunitResult test_make_cell_from_values(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = make_cell("TestFName", "TestLName", "10000");
    munit_assert_string_equal("TestFName", c->fname);
    munit_assert_string_equal("TestLName", c->lname);
    munit_assert_string_equal("10000", c->zip);
    return MUNIT_OK;
}

static MunitResult test_make_cell_from_line(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}


/* Printing
======== */

static MunitResult test_smoke_print_cell_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = NULL;
    print_cell(c);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_cell_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = make_cell("", "", "");
    print_cell(c);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_cell_full(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = make_cell("TestFName", "TestLName", "10000");
    print_cell(c);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_smoke_print_list_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_smoke_print_list_full(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

/* Comparison
========== */

static MunitResult test_compare_cells_lname_gt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_compare_cells_lname_lt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_compare_cells_lname_eq_fname_gt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

static MunitResult test_compare_cells_lname_eq_fname_lt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    return MUNIT_FAIL;
}

/* Insertion 
========= */

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