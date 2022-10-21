#include "munit/munit.h"
#include "../src/llist.h"



/* =========================================================================
                              Test Helpers
 =========================================================================*/


static void suppress_print_output() {
    freopen ("/dev/null", "w", stdout);
}

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

static void free_static_lcell(struct lcell *lc) {
	free_static_list(lc->lst);
    free(lc);
}

static void free_static_lcells(struct llist* llst) {
    struct lcell* cur;
	struct lcell* tmp;
    /* Uninitialized list */
	if (llst == NULL) { 
        error_msg("Uninitialized list pointer.");
    }
    /* Free each lcell one by one -> free the underlying lists */
	cur = llst->head;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
		free_static_lcell(tmp);
	}
	llst->head = NULL;
}

void free_static_llist(struct llist* llst) {
    free_static_lcells(llst);
    free(llst);
}



/* =========================================================================
                              List Tests
 =========================================================================*/

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
    free(c);
    return MUNIT_OK;
}

static MunitResult test_make_cell_from_line(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = make_cell_from_line("TestFName,TestLName,10000;");
    munit_assert_string_equal("TestFName", c->fname);
    munit_assert_string_equal("TestLName", c->lname);
    munit_assert_string_equal("10000", c->zip);
    free(c->fname);
    free(c->lname);
    free(c->zip);
    free(c);
    return MUNIT_OK;
}

/* Printing
======== */

static MunitResult test_smoke_print_cell_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = make_cell("", "", "");
    suppress_print_output();
    print_cell(c);
    free(c);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_cell_full(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = make_cell("TestFName", "TestLName", "10000");
    suppress_print_output();
    print_cell(c);
    free(c);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_list_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    lst = new_list();
    suppress_print_output();
    print_list(lst);
    free_list(lst);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_list_full(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* c2;
    lst = new_list();
    c1 = make_cell("TestFName1", "TestLName1", "10001");
    c2 = make_cell("TestFName2", "TestLName2", "10002");
    push(lst,c2);
    push(lst,c1);
    suppress_print_output();
    print_list(lst);
    free_static_list(lst);
    return MUNIT_OK;
}

/* Comparison
========== */

static MunitResult test_compare_cells_lname_gt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = make_cell("Aaaa", "BBBB", "10001");
    c2 = make_cell("Aaaa", "AAAA", "10002");
    int res = compare_cells(c1, c2);
    munit_assert_true(res >= 0);
    free(c1);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_cells_lname_lt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = make_cell("Aaaa", "AAAA", "10001");
    c2 = make_cell("Aaaa", "BBBB", "10002");
    int res = compare_cells(c1, c2);
    munit_assert_true(res <= 0);
    free(c1);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_cells_lname_eq_fname_gt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = make_cell("Bbbb", "AAAA", "10001");
    c2 = make_cell("Aaaa", "AAAA", "10002");
    int res = compare_cells(c1, c2);
    munit_assert_true(res >= 0);
    free(c1);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_cells_lname_eq_fname_lt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = make_cell("Aaaa", "AAAA", "10001");
    c2 = make_cell("Bbbb", "AAAA", "10002");
    int res = compare_cells(c1, c2);
    munit_assert_true(res <= 0);
    free(c1);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_cells_lname_eq_fname_eq(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = make_cell("Bbbb", "AAAA", "10001");
    c2 = make_cell("Bbbb", "AAAA", "10002");
    int res = compare_cells(c1, c2);
    munit_assert_true(res == 0);
    free(c1);
    free(c2);
    return MUNIT_OK;
}

/* Push
===== */

static MunitResult test_push_empty_list(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c;
    lst = new_list();
    c = make_cell("TestFName1", "TestLName1", "10001");
    push(lst,c);
    munit_assert_true(compare_cells(lst->head, c) == 0);
    munit_assert_null(c->next);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_push(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* c2;
    lst = new_list();
    c1 = make_cell("TestFName1", "TestLName1", "10001");
    c2 = make_cell("TestFName2", "TestLName2", "10002");
    push(lst,c2);
    push(lst,c1);
    munit_assert_true(compare_cells(c1->next, c2) == 0);
    munit_assert_null(c2->next);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_pop(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* c1_cpy;
    struct cell* c2;
    struct cell* out;
    out = (struct cell*) malloc(sizeof(struct cell));
    lst = new_list();
    c1 = make_cell("TestFName1", "TestLName1", "10001");
    c1_cpy = make_cell("TestFName1", "TestLName1", "10001");
    c2 = make_cell("TestFName2", "TestLName2", "10002");
    push(lst,c2);
    push(lst,c1);
    pop(lst, out);
    munit_assert_true(compare_cells(lst->head, c2) == 0);
    munit_assert_null(c2->next);
    munit_assert_true(compare_cells(out, c1_cpy) == 0);
    free_static_list(lst);
    free(out);
    free(c1_cpy);
    return MUNIT_OK;
}

/* Insertion 
========= */

static MunitResult test_insert_empty_list(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    lst = new_list();
    c1 = make_cell_from_line("Quentin,DUCASSE,10000");
    insert(lst, c1);
    munit_assert_true(compare_cells(lst->head, c1) == 0);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_insert_first(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* c2;
    struct cell* new;
    lst = new_list();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    c2 = make_cell_from_line("Emilien,FOURNIER,10000");
    new = make_cell_from_line("Antoine,ARNAUD,10000");
    push(lst, c2);
    push(lst, c1);
    insert(lst, new);
    munit_assert_true(compare_cells(lst->head, new) == 0);
    munit_assert_true(compare_cells(new->next, c1) == 0);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_insert_middle(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* c2;
    struct cell* new;
    lst = new_list();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    c2 = make_cell_from_line("Emilien,FOURNIER,10000");
    new = make_cell_from_line("Quentin,DUCASSE,10000");
    push(lst, c2);
    push(lst, c1);
    insert(lst, new);
    munit_assert_true(compare_cells(c1->next, new) == 0);
    munit_assert_true(compare_cells(new->next, c2) == 0);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_insert_last(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* c2;
    struct cell* new;
    lst = new_list();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    c2 = make_cell_from_line("Emilien,FOURNIER,10000");
    new = make_cell_from_line("Zinedine,ZIDANE,10000");
    push(lst, c2);
    push(lst, c1);
    insert(lst, new);
    munit_assert_true(compare_cells(c2->next, new) == 0);
    munit_assert_null(new->next);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_insert_same_lname_lt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* new;
    lst = new_list();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    new = make_cell_from_line("Arnaud,BERTRAND,10000");
    push(lst, c1);
    insert(lst, new);
    munit_assert_true(compare_cells(lst->head, new) == 0);
    munit_assert_true(compare_cells(new->next, c1) == 0);
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_insert_same_lname_gt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c1;
    struct cell* new;
    lst = new_list();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    new = make_cell_from_line("Zinedine,BERTRAND,10000");
    push(lst, c1);
    insert(lst, new);
    munit_assert_true(compare_cells(c1->next, new) == 0);
    munit_assert_null(new->next);
    free_static_list(lst);
    return MUNIT_OK;
}

/* Load file
========= */

static MunitResult test_load_file(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell *c1, *c2, *c3, *c4, *c5, *c6;
    c1 = make_cell("Samir","ARNAUD","70337");
    c2 = make_cell("Geneviève","BERTRAND","64084");
    c3 = make_cell("Lina","CORINE","53263");
    c4 = make_cell("Michel","CORINE","54635");
    c5 = make_cell("Marco","FOURNIER","74161");
    c6 = make_cell("Jessy","ZIDANE","84067");
    lst = load_file("mutests/test_file_list.txt");
    munit_assert_true(compare_cells(lst->head, c1) == 0);
    munit_assert_true(compare_cells(lst->head->next, c2) == 0);
    munit_assert_true(compare_cells(lst->head->next->next, c3) == 0);
    munit_assert_true(compare_cells(lst->head->next->next->next, c4) == 0);
    munit_assert_true(compare_cells(lst->head->next->next->next->next, c5) == 0);
    munit_assert_true(compare_cells(lst->head->next->next->next->next->next, c6) == 0);
    munit_assert_null(lst->head->next->next->next->next->next->next);
    free_list(lst);
    free(c1);
    free(c2);
    free(c3);
    free(c4);
    free(c5);
    return MUNIT_OK;
}


/* =========================================================================
                              List NULL checks
 =========================================================================*/

/* NULL checks
=========== */

static MunitResult test_free_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    lst = NULL;
    free_list(lst);
    return MUNIT_OK;
}

static MunitResult test_free_static_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    lst = NULL;
    free_static_list(lst);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_cell_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    c = NULL;
    print_cell(c);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    lst = NULL;
    print_list(lst);
    return MUNIT_OK;
}

static MunitResult test_compare_cells_c1_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = NULL;
    c2 = make_cell("Bbbb", "AAAA", "10002");
    compare_cells(c1, c2);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_cells_c2_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    c1 = make_cell("Bbbb", "AAAA", "10001");
    c2 = NULL;
    compare_cells(c1, c2);
    free(c1);
    return MUNIT_OK;
}

static MunitResult test_push_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c;
    lst = NULL;
    c = make_cell("TestFname", "TestLname", "10000");
    push(lst, c);
    return MUNIT_OK;
}

static MunitResult test_push_cell_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c;
    lst = new_list();
    c = NULL;
    push(lst, c);
    return MUNIT_OK;
}

static MunitResult test_pop_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* out;
    lst = NULL;
    out = (struct cell*) malloc(sizeof(struct cell));
    pop(lst, out);
    return MUNIT_OK;
}

static MunitResult test_insert_list_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c;
    lst = NULL;
    c = make_cell("TestFname", "TestLname", "10000");
    insert(lst, c);
    return MUNIT_OK;
}

static MunitResult test_insert_cell_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c;
    lst = new_list();
    c = NULL;
    insert(lst, c);
    return MUNIT_OK;
}

static MunitResult test_load_file_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    lst = load_file("unknown_file");
    free_list(lst);
    return MUNIT_OK;
}

/* =========================================================================
                              LList Tests
 =========================================================================*/

/* LCell making
============ */

static MunitResult test_make_lcell_from_values(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct list* lst;
    struct cell* c;
    struct lcell* lc;
    lst = new_list();
    c = make_cell("TestFname", "TestLname", "10000");
    push(lst, c);
    lc = make_lcell('T', lst);
    munit_assert_char('T', ==, lc->letter);
    munit_assert_true(compare_cells(c, lc->lst->head) == 0);
    return MUNIT_OK;
}

static MunitResult test_make_lcell_from_cell(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    struct lcell* lc;
    c = make_cell("TestFname", "TestLname", "10000");
    lc = make_lcell_from_cell(c);
    munit_assert_char('T', ==, lc->letter);
    munit_assert_true(compare_cells(c, lc->lst->head) == 0);
    free_static_lcell(lc);
    return MUNIT_OK;
}

/* Printing
======== */

static MunitResult test_smoke_print_lcell_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    struct lcell* lc;
    c = make_cell("", "", "");
    lc = make_lcell_from_cell(c);
    suppress_print_output();
    print_lcell(lc);
    free_static_lcell(lc);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_lcell_full(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c;
    struct lcell* lc;
    c = make_cell("TestFname", "TestLname", "10000");
    lc = make_lcell_from_cell(c);
    suppress_print_output();
    print_lcell(lc);
    free_static_lcell(lc);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_llist_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    llst = new_llist();
    suppress_print_output();
    print_llist(llst);
    free_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_llist_full(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    struct lcell* lc1;
    struct lcell* lc2;
    struct llist* llst;
    llst = new_llist();
    c1 = make_cell("TestFname1", "TestLname1", "10001");
    c2 = make_cell("TestFname2", "TestLname2", "10002");
    lc1 = make_lcell_from_cell(c1);
    lc2 = make_lcell_from_cell(c2);
    lpush(llst, lc2);
    lpush(llst, lc1);
    suppress_print_output();
    print_llist(llst);
    free_static_llist(llst);
    return MUNIT_OK;
}

/* Comparison
========== */

static MunitResult test_compare_lcells_gt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    struct lcell* lc;
    c1 = make_cell("Aaaa", "AAAA", "10000");
    c2 = make_cell("Bbbb", "BBBB", "10000");
    lc = make_lcell_from_cell(c1);
    munit_assert_true(compare_lcells(lc, c2) >= 0);
    free_static_lcell(lc);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_lcells_lt(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    struct lcell* lc;
    c1 = make_cell("Bbbb", "BBBB", "10000"); 
    c2 = make_cell("Aaaa", "AAAA", "10000");
    lc = make_lcell_from_cell(c1);
    munit_assert_true(compare_lcells(lc, c2) <= 0);
    free_static_lcell(lc);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_lcells_eq(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell* c1;
    struct cell* c2;
    struct lcell* lc;
    c1 = make_cell("Bbbb", "BBBB", "10000"); 
    c2 = make_cell("Aaaa", "BAAA", "10000");
    lc = make_lcell_from_cell(c1);
    munit_assert_true(compare_lcells(lc, c2) == 0);
    free_static_lcell(lc);
    free(c2);
    return MUNIT_OK;
}

/* Insertion
========= */

static MunitResult test_linsert_empty_list(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    struct cell* c1;
    llst = new_llist();
    c1 = make_cell_from_line("Quentin,DUCASSE,10000");
    linsert(llst, c1);
    munit_assert_true(compare_lcells(llst->head, c1) == 0);
    munit_assert_true(compare_cells(llst->head->lst->head, c1) == 0);
    free_static_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_linsert_first(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell *c1, *c2, *new;
    struct lcell *lc1, *lc2;
    struct llist* llst;
    llst = new_llist();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    c2 = make_cell_from_line("Emilien,FOURNIER,10000");
    new = make_cell_from_line("Antoine,ARNAUD,10000");
    lc1 = make_lcell_from_cell(c1);
    lc2 = make_lcell_from_cell(c2);
    lpush(llst, lc2);
    lpush(llst, lc1);
    linsert(llst, new);
    munit_assert_true(compare_lcells(llst->head, new) == 0);
    munit_assert_true(compare_cells(llst->head->lst->head, new) == 0);
    munit_assert_char(llst->head->letter, ==, new->lname[0]);
    munit_assert_null(llst->head->lst->head->next);
    free_static_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_linsert_middle(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell *c1, *c2, *new;
    struct lcell *lc1, *lc2;
    struct llist* llst;
    llst = new_llist();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    c2 = make_cell_from_line("Emilien,FOURNIER,10000");
    new = make_cell_from_line("Quentin,DUCASSE,10000");
    lc1 = make_lcell_from_cell(c1);
    lc2 = make_lcell_from_cell(c2);
    lpush(llst, lc2);
    lpush(llst, lc1);
    linsert(llst, new);
    munit_assert_true(compare_lcells(llst->head->next, new) == 0);
    munit_assert_true(compare_cells(llst->head->next->lst->head, new) == 0);
    munit_assert_char(llst->head->next->letter, ==, new->lname[0]);
    munit_assert_null(llst->head->next->lst->head->next);
    free_static_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_linsert_last(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell *c1, *c2, *new;
    struct lcell *lc1, *lc2;
    struct llist* llst;
    llst = new_llist();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    c2 = make_cell_from_line("Emilien,FOURNIER,10000");
    new = make_cell_from_line("Zinedine,ZIDANE,10000");
    lc1 = make_lcell_from_cell(c1);
    lc2 = make_lcell_from_cell(c2);
    lpush(llst, lc2);
    lpush(llst, lc1);
    linsert(llst, new);
    munit_assert_true(compare_lcells(llst->head->next->next, new) == 0);
    munit_assert_true(compare_cells(llst->head->next->next->lst->head, new) == 0);
    munit_assert_char(llst->head->next->next->letter, ==, new->lname[0]);
    munit_assert_null(llst->head->next->next->lst->head->next);
    free_static_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_linsert_exist(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    struct cell *c1, *new;
    struct lcell* lc1;
    llst = new_llist();
    c1 = make_cell_from_line("Michel,BERTRAND,10000");
    new = make_cell_from_line("Arnaud,BERTRAND,10000");
    lc1 = make_lcell_from_cell(c1);
    lpush(llst, lc1);
    linsert(llst, new);
    munit_assert_true(compare_lcells(llst->head, new) == 0);
    munit_assert_true(compare_cells(llst->head->lst->head, new) == 0);
    munit_assert_true(compare_cells(llst->head->lst->head->next, c1) == 0);
    munit_assert_null(c1->next);
    free_static_llist(llst);
    return MUNIT_OK;
}

/* File loading
============ */

static MunitResult test_lload_file(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    struct cell *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8;
    c1 = make_cell("Samir","ARNAUD","70337");
    c2 = make_cell("Geneviève","BERTRAND","64084");
    c3 = make_cell("André","CANARD","65734");
    c4 = make_cell("Lina","CORINE","53263");
    c5 = make_cell("Michel","CORINE","54635");
    c6 = make_cell("Marco","FOURNIER","74161");
    c7 = make_cell("Jessy","ZIDANE","84067");
    c8 = make_cell("Zinédine","ZIDANE","78400");
    llst = lload_file("mutests/test_file_llist.txt");
    /* lcell A */
    munit_assert_char(llst->head
                        ->letter, ==, 'A');
    munit_assert_true(compare_cells(llst->head
                                    ->lst->head, c1) == 0);
    munit_assert_null(llst->head
                        ->lst->head->next);
    /* lcell B */
    munit_assert_char(llst->head->next
                        ->letter, ==, 'B');
    munit_assert_true(compare_cells(llst->head->next
                        ->lst->head, c2) == 0);
    munit_assert_null(llst->head->next
                        ->lst->head->next);
    /* lcell C */
    munit_assert_char(llst->head->next->next
                        ->letter, ==, 'C');
    munit_assert_true(compare_cells(llst->head->next->next
                        ->lst->head, c3) == 0);
    munit_assert_true(compare_cells(llst->head->next->next
                        ->lst->head->next, c4) == 0);
    munit_assert_true(compare_cells(llst->head->next->next
                        ->lst->head->next->next, c5) == 0);
    munit_assert_null(llst->head->next->next
                        ->lst->head->next->next->next);
    /* lcell F */
    munit_assert_char(llst->head->next->next->next
                        ->letter, ==, 'F');
    munit_assert_true(compare_cells(llst->head->next->next->next
                        ->lst->head, c6) == 0);
    munit_assert_null(llst->head->next->next->next
                        ->lst->head->next);
    /* lcell Z */
    munit_assert_char(llst->head->next->next->next->next
                            ->letter, ==, 'Z');
    munit_assert_true(compare_cells(llst->head->next->next->next->next
                            ->lst->head, c7) == 0);
    munit_assert_true(compare_cells(llst->head->next->next->next->next
                            ->lst->head->next, c8) == 0);
    munit_assert_null(llst->head->next->next->next->next
                            ->lst->head->next->next);
    free_llist(llst);
    free(c1);
    free(c2);
    free(c3);
    free(c4);
    free(c5);
    free(c6);
    free(c7);
    free(c8);
    return MUNIT_OK;
}


/* =========================================================================
                            LList NULL Checks
 =========================================================================*/

static MunitResult test_free_llist_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    llst = NULL;
    free_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_free_static_llist_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    llst = NULL;
    free_static_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_lcell_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct lcell* lc;
    lc = NULL;
    print_lcell(lc);
    return MUNIT_OK;
}

static MunitResult test_smoke_print_llist_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    llst = NULL;
    print_llist(llst);
    return MUNIT_OK;
}

static MunitResult test_compare_lcells_c1_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct lcell* lc1;
    struct cell* c2;
    lc1 = NULL;
    c2 = make_cell("Bbbb", "AAAA", "10002");
    compare_lcells(lc1, c2);
    free(c2);
    return MUNIT_OK;
}

static MunitResult test_compare_lcells_c2_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct cell *c1, *c2;
    struct lcell *lc1;
    c1 = make_cell("Bbbb", "AAAA", "10001");
    lc1 = make_lcell_from_cell(c1);
    c2 = NULL;
    compare_lcells(lc1, c2);
    free_static_lcell(lc1);
    return MUNIT_OK;
}

static MunitResult test_linsert_llist_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    struct cell* c;
    llst = NULL;
    c = make_cell("TestFname", "TestLname", "10000");
    linsert(llst, c);
    return MUNIT_OK;
}

static MunitResult test_linsert_cell_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    struct cell* c;
    llst = new_llist();
    c = NULL;
    linsert(llst, c);
    return MUNIT_OK;
}

static MunitResult test_lload_file_null(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    struct llist* llst;
    llst = lload_file("unknown_file");
    free_llist(llst);
    return MUNIT_OK;
}

/* =========================================================================
                           Test Suites and Main
 =========================================================================*/

/* Test Suite
========== */

static MunitTest general_list_tests[] = {
    {(char*) "/print/cell/empty", test_smoke_print_cell_empty,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/cell/full",  test_smoke_print_cell_full,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/list/empty", test_smoke_print_list_empty,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/list/full",  test_smoke_print_list_full,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/make/cell/values", test_make_cell_from_values,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/make/cell/line",   test_make_cell_from_line,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/gt",       test_compare_cells_lname_gt,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/lt",       test_compare_cells_lname_lt,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/eqgt",     test_compare_cells_lname_eq_fname_gt,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/eqlt",     test_compare_cells_lname_eq_fname_lt,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/eqeq",     test_compare_cells_lname_eq_fname_eq,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/push/empty",       test_push_empty_list,                  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/push",             test_push,                             NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/pop",              test_pop,                              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/empty",     test_insert_empty_list,                NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/first",     test_insert_first,                     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/middle",    test_insert_middle,                    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/last",      test_insert_last,                      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/eqlt",      test_insert_same_lname_lt,             NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/eqgt",      test_insert_same_lname_gt,             NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/load-file",        test_load_file,                        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitTest null_list_tests[] = {
    {(char*) "/free/list/null-list",     test_free_list_null,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/free/sta-list/null-list", test_free_static_list_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/cell/null-cell",    test_smoke_print_cell_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/list/null-list",    test_smoke_print_list_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/null-c1",         test_compare_cells_c1_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/null-c2",         test_compare_cells_c2_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/null-list",        test_insert_list_null,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/insert/null-cell",        test_insert_cell_null,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/push/null-list",          test_push_list_null,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/push/null-cell",          test_push_cell_null,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/pop/null-list",           test_pop_list_null,               NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/load-file/null-file",     test_load_file_null,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitTest general_llist_tests[] = {
    {(char*) "/print/lcell/empty", test_smoke_print_lcell_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/lcell/full",  test_smoke_print_lcell_full,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/llist/empty", test_smoke_print_llist_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/llist/full",  test_smoke_print_llist_full,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/make/lcell/values", test_make_lcell_from_values,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/make/lcell/cell",   test_make_lcell_from_cell,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/llgt",      test_compare_lcells_gt,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/lllt",      test_compare_lcells_lt,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/lleq",      test_compare_lcells_eq,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/empty",     test_linsert_empty_list,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/first",     test_linsert_first,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/middle",    test_linsert_middle,          NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/last",      test_linsert_last,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/exist",     test_linsert_exist,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/lload-file",        test_lload_file,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitTest null_llist_tests[] = {
    {(char*) "/free/llist/null-llist",     test_free_llist_null,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/free/sta-llist/null-llist", test_free_static_llist_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/lcell/null-lcell",    test_smoke_print_lcell_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/print/llist/null-llist",    test_smoke_print_llist_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/null-lc1",          test_compare_lcells_c1_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/compare/null-c2",           test_compare_lcells_c2_null,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/null-list",         test_linsert_llist_null,           NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/linsert/null-cell",         test_linsert_cell_null,            NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*) "/load-file/null-file",       test_lload_file_null,              NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite general_list_suite = { 
    (char*) "/list", general_list_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

static const MunitSuite null_list_suite = { 
    (char*) "/list/null", null_list_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

static const MunitSuite general_llist_suite = { 
    (char*) "/llist", general_llist_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

static const MunitSuite null_llist_suite = { 
    (char*) "/llist/null", null_llist_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

#include <stdlib.h>
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    munit_suite_main(&general_list_suite, (void*) "munit", argc, argv);
    munit_suite_main(&null_list_suite, (void*) "munit", argc, argv);
    munit_suite_main(&general_llist_suite, (void*) "munit", argc, argv);
    munit_suite_main(&null_llist_suite, (void*) "munit", argc, argv);
    return 0;
}