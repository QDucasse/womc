#include "list.h"

struct llist {
    struct lcell* head;
};

struct lcell {
    char letter;
    struct list* lst;
    struct lcell* next;
};

/* Allocates memory for a llist structure and returns the pointer */
struct llist* new_llist();

/* Frees the input llist and its cells */
void free_lcell(struct lcell* lcell);

/* Frees the input llist and its cells */
void free_llist(struct llist* llst);

/* Print an lcell, the letter followed by the underlying list */
void print_lcell(struct lcell* lc);

/* Print an llist, a succession of lcells */
void print_llist(struct llist* lst);

/* Creates an lcell from given fields */
struct lcell* make_lcell(char letter, struct list* lst);

/* Creates an lcell from given fields */
struct lcell* make_lcell_from_cell(struct cell* c);

/* Push an lcell on top of an llist (no processing) */
void lpush(struct llist* llst, struct lcell* lc);

/* Compare the lnames then names of two records */
int compare_lcells(struct lcell* a, struct cell* b);

/* Adds the cell to the corresponding lcell (or creates a new lcell with the first letter) */
void linsert(struct llist* llst, struct cell* c);

struct llist* lload_file(char* file_name);

