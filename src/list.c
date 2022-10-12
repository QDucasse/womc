#include "list.h"

/* Error handling
============== */

void error_msg(char* msg) {
    printf("Error: in %s:%d - %s(): %s\n", __FILE__, __LINE__, __func__,  msg);
    exit(EXIT_FAILURE);
}


/* Construction/Destruction
======================== */

struct list* new_list() {
	struct list* lst = (struct list*)malloc(sizeof(struct list));

	if (lst == NULL) { 
		error_msg("malloc() failed.");
	}

	lst->head=NULL;
	return lst;
}

static void free_cells(struct list *lst) {
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
        free(tmp->fname);
        free(tmp->lname);
        free(tmp->zip);
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
	if (c == NULL) { 
        error_msg("Uninitialized cell pointer.");
     }
    printf("[%s, %s, %s]", c->fname, c->lname, c->zip);
}

void print_list(struct list* lst) {
	struct cell *cur;

	if (lst == NULL) { 
        error_msg("Uninitialized list pointer.");
     }
	
	cur = lst->head;
	printf("{");
    /* Check for an empty list */
	if(cur==NULL){
		printf("}\n");
		return;
	}
	while(cur->next != NULL)
	{
		print_cell(cur);
        printf(",\n");
		cur=cur->next;
	}
    print_cell(cur);
	printf("}\n");
}


/* Adding/removing cells
===================== */

void push_with_values(struct list *lst, char* fname, char* lname, char* zip) {
	struct cell * c;
    c = make_cell(fname, lname, zip);
    push(lst, c);
}

void push(struct list *lst, struct cell* c) {
    if (lst == NULL) { 
		error_msg("Uninitialized list pointer.");
	}
    /* Append to the head of the list */
	c->next = lst->head;
	lst->head = c;
}

void pop(struct list *lst, struct cell* out){
	struct cell *c;

	if (lst == NULL) { 
		error_msg("Uninitialized list pointer.");
	}

	c = lst->head;
	if (c==NULL) {
		error_msg("List is empty.");
	}

	memcpy(out, c, sizeof(struct cell));
	lst->head = c->next;
	free(c);
}

/* Comparison/Sorting
================== */

int compare_cells(struct cell* a, struct cell* b){
    int res;
    /* First compare the last names */
    res = strcmp(a->lname, b->lname);
    /* In case of equality, compare first names */
    if (res == 0) {
        res = strcmp(a->fname, b->fname);
    }
    return res;
}

void insert(struct list* lst, struct cell* c) {
    /* Uninitialized list check */
    if (lst == NULL) {
        error_msg("Uninitialized list pointer.");
    }
    /* Empty list check OR first of the list */
    if (lst->head == NULL || compare_cells(c, lst->head) < 0) {
        c->next = lst->head;
        lst->head = c;
    } else {
        struct cell* cur;
        cur = lst->head;
        /* Look for correct place */
        while (cur->next != NULL && compare_cells(c, cur->next) >= 0) {
            cur = cur->next;
        }
        /* Insert cell */
        c->next = cur->next;
        cur->next = c;
    }
}

/* Cell creation
============= */

struct cell* make_cell(char* fname, char* lname, char* zip) {
    struct cell * c;
    // Allocate memory for the cell
	c = malloc(sizeof(struct cell));
	if (c == NULL) {
		error_msg("malloc() failed.");
	}
    /* Fill fields */
	c->fname = fname;
    c->lname = lname;
    c->zip = zip;
    c->next = NULL;
    return c;
}


struct cell* make_cell_from_line(char* line) {
    char* fname = (char*) malloc(NAME_LENGTH * sizeof(char));
    char* lname = (char*) malloc(NAME_LENGTH * sizeof(char));
    char* zip = (char*) malloc(ZIP_LENGTH * sizeof(char));
    if (fname == NULL || lname == NULL || zip == NULL) {
		error_msg("malloc() failed.");
	}
    /* Extract values and copy the result */
    strcpy(fname, strtok(line, ","));
    strcpy(lname, strtok(NULL, ","));
    strcpy(zip, strtok(NULL, ";"));
    return make_cell(fname, lname, zip);
}

/* File handling
============= */

struct list* load_file(char* file_name) {
    struct cell* cur;
    struct list* l;
    char line[256];
    FILE* file;

    /* Open the file */
    file = fopen(file_name, "r");
    if (file == NULL) {
        error_msg("File not recognized.");
    }

    /* Note: the malloc should be done here and not before the file opening
    because if the file is not recognized, the allocated memory is lost. */
    l = new_list();

    /* Parse and insert line by line */
    while (fgets(line, sizeof(line), file)) {
        cur = make_cell_from_line(line);
        insert(l, cur);
    }

    fclose(file);

    return l;
}