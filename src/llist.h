#include "list.h"

struct llist {
    struct lcell* head;
};

struct lcell {
    char letter;
    struct list* lst;
    struct lcell* next;
};

struct llist* new_llist();
void free_lcells(struct llist* llst);
void free_llist(struct llist* llst);
void print_cell(struct lcell* lc);
void print_llist(struct llist* lst);

void lpush(struct llist *llst, struct lcell* lc);
void linsert(struct llist* llst, struct cell* c);
int compare_lcells(struct lcell* a, struct cell* b);
struct llist* lload_file(char* file_name);

