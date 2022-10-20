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

    return 0;
}