#include "list.h"

/* Construction/Destruction
======================== */

struct list* new_list() {
	struct list* lst = (struct list*)malloc(sizeof(struct list));

	if (lst == NULL) { 
		return NULL; 
	}

	lst->head=NULL;
	return lst;
}

static void free_cells(struct list *lst) {
	struct cell *cur;
	struct cell *tmp;
    // Empty list 
	if (lst == NULL) { 
        return; 
    }
    // Free each cell one by one
	cur = lst->head;
	while (cur != NULL) {
		tmp = cur;
		cur = cur->next;
        // If dynamically allocated!
        // free(tmp->fname);
        // free(tmp->lname);
        // free(tmp->zip);
		free(tmp);
	}
	lst->head = NULL;
}

void free_list(struct list* lst) {
    free_cells(lst);
	free(lst);
}


/* Printing
======== */

void print_cell(struct cell* c) {
	/* Your code here */
}

void print_list(struct list *lst) {
	/* Your code here */
}

/* Cell addition
============= */

struct cell* make_cell(char* fname, char* lname, char* zip) {
	/* Your code here */
}

void push(struct list *lst, struct cell* c) {
	/* Your code here */
}
