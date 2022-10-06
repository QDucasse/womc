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

char* new_string(char* str) {
    char* new_str = malloc(sizeof(char) * strlen(str));
    strcpy(str, new_str);
    return new_str;
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
    printf("[%s, %s, %s]", c->fname, c->lname, c->zip);
}

void print_list(struct list* lst) {
	struct cell *cur;

	if (lst == NULL) { return; }
	
	cur = lst->head;
	printf("{");
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
    c = make_cell_from_values(fname, lname, zip);
    push(lst, c);
}

void push(struct list *lst, struct cell* c) {
    // Append to the head of the list
	c->next = lst->head;
	lst->head = c;
}

void pop(struct list *lst, struct cell* out){
	struct cell *c;

	if (lst == NULL) { 
		// return NULL_LIST_ERROR;  
	}

	c = lst->head;
	if (c==NULL) {
		// return EMPTY_LIST_ERROR;
	}

	out = c;
	lst->head = c->next;
	free(c);
}

/* Comparison/Sorting
================== */

int compare_cells(struct cell* a, struct cell* b){
    int res;
    res = strcmp(a->lname, b->lname);
    if (res == 0) {
        res = strcmp(a->fname, b->fname);
    }
    return res;
}

void insert(struct list* lst, struct cell* c) {
    // Uninitialized list check
    if (lst == NULL) {
        // return NULL_LIST_ERROR;
    }
    // Empty list check OR first of the list
    if (lst->head == NULL || compare_cells(c, lst->head) < 0) {
        c->next = lst->head;
        lst->head = c;
    } else {
        struct cell* cur;
        cur = lst->head;
        // Look for correct place
        while (cur->next != NULL && compare_cells(c, cur->next) >= 0) {
            cur = cur->next;
        }
        // Insert cell
        c->next = cur->next;
        cur->next = c;
    }
}

/* Cell creation
============= */

struct cell* make_cell_from_values(char* fname, char* lname, char* zip) {
    struct cell * c;
    // Allocate memory for the cell
	c = malloc(sizeof(struct cell));
	if (c == NULL) {
		// return ALLOCATION_ERROR;
	}
    // Fill fields
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
    // Extract values
    strcpy(fname, strtok(line, ","));
    strcpy(lname, strtok(NULL, ","));
    strcpy(zip, strtok(NULL, ";"));
    return make_cell_from_values(fname, lname, zip);
}

/* File handling
============= */

struct list* load_file(char* file_name) {
    struct cell* cur;
    char line[256];
    struct list* l = new_list();

    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        return NULL; // error
    }

    while (fgets(line, sizeof(line), file)) {
        cur = make_cell_from_line(line);
        insert(l, cur);
    }

    fclose(file);

    return l;
}