#include "llist.h"

/* Construction/Destruction
======================== */

struct llist* new_llist() {
	struct llist* llst = (struct llist*)malloc(sizeof(struct list));

	if (llst == NULL) { 
		error_msg("Uninitialized list pointer.");
	}

	llst->head=NULL;
	return llst;
}

static void free_lcells(struct llist* llst) {
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
		free_list(tmp->lst);
        free(tmp);
	}
	llst->head = NULL;
}

void free_llist(struct llist* llst) {
    free_lcells(llst);
    free(llst);
}

/* Printing
======== */

void print_lcell(struct lcell* lc) {
    printf("[%c] ", lc->letter);
    print_list(lc->lst);
}

void print_llist(struct llist* lst) {
	struct lcell *cur;

	if (lst == NULL) { 
        error_msg("Uninitialized list pointer.");
     }
	
	cur = lst->head;
	printf("{{");
	if(cur==NULL){
		printf("}}\n");
		return;
	}
	while(cur->next != NULL)
	{
		print_lcell(cur);
        printf(",\n");
		cur=cur->next;
	}
    print_lcell(cur);
	printf("}}\n");
}

/* Adding/removing cells
===================== */

struct lcell* make_lcell(char letter, struct list* lst) {
    struct lcell * lc;
    /* Allocate memory for the cell */
	lc = malloc(sizeof(struct lcell));
	if (lc == NULL) {
		error_msg("malloc() failed.");
	}
    /* Fill fields */
	lc->letter = letter;
    lc->lst = lst;
    lc->next = NULL;
    return lc;
}

struct lcell* make_lcell_from_cell(struct cell* c) {
    struct lcell* lc;
    struct list* lst;
    /* Create the internal list with the cell */
    lst = new_list();
    push(lst, c);
    /* Create the lcell with the fresh list and add it */
    lc = make_lcell(c->lname[0], lst);
    return lc;
}

int compare_lcells(struct lcell* a, struct cell* b) {
    return b->lname[0] - a->letter;
}

void linsert(struct llist* llst, struct cell* c) {
    /* Uninitialized list check */
    if (llst == NULL) {
        error_msg("Uninitialized llist.");
    }
    /* Empty list check OR first of the list */
    if (llst->head == NULL || compare_lcells(llst->head, c) < 0) {
        /* Create a new lcell with a new list */
        struct lcell* lc;
        lc = make_lcell_from_cell(c);
        /* Add it to on the top of the llist */
        lc->next = llst->head;
        llst->head = lc;
    } else { 
        /* If we are here, the list is not empty and the name does not come before the first letter already in */
        /* Look for correct place */
        struct lcell* cur;
        cur = llst->head;
        while (cur->next != NULL && compare_lcells(cur->next, c) > 0) {
            cur = cur->next;
        }
        /* Add to the current lcell if equal */
        if (compare_lcells(cur, c) == 0) {
            insert(cur->lst, c); // Sane
        } else if (cur->next != NULL && compare_lcells(cur->next, c) == 0) {
            insert(cur->next->lst, c);
        } else {
            /* Create a new lcell with a new list */
            struct lcell* lc;
            lc = make_lcell_from_cell(c);
            lc->next = cur->next;
            cur->next = lc;
        }
    }
}

/* File handling
============= */

struct llist* lload_file(char* file_name) {
    struct cell* cur;
    char line[256];
    struct llist* llst;
    FILE* file;

    /* Open the file */
    file = fopen(file_name, "r");
    if (file == NULL) {
        error_msg("File not recognized");
    }

    /* Note: the malloc should be done here and not before the file opening
    because if the file is not recognized, the allocated memory is lost. */
    llst = new_llist();

    /* Parse and insert line by line */
    while (fgets(line, sizeof(line), file)) {
        cur = make_cell_from_line(line);
        linsert(llst, cur);
    }

    fclose(file);

    return llst;
}
