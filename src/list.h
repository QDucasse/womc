#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_LENGTH 40
#define ZIP_LENGTH 10

struct list {
    struct cell* head;
};

struct cell {
    char* fname;
    char* lname;
    char* zip;
    struct cell* next;
};

/* Prints the given message and exits */
void error_msg(char* msg);

/* Allocates memory for a list structure and returns the pointer */
struct list* new_list();

/* Frees the input list and its cells */
void free_list(struct list* lst);

/* Print a list and its cells */
void print_list(struct list *lst);

/* Push a new cell with given value at the beginning of the list */
void push_with_values(struct list* lst, char* name, char* lname, char* zip);

/* Push a cell on top */
void push(struct list *lst, struct cell* c);

/* Pop the head of the list in the given out pointer */
void pop(struct list* lst, struct cell* out);

/* Compare the lnames then names of two records */
int compare_cells(struct cell* a, struct cell* b);

/* Adds the cell to the list respecting alphabetical order of names/lnames */
void insert(struct list* lst, struct cell* c);

/* Creates a cell from given fields */
struct cell* make_cell(char* fname, char* lname, char* zip);

/* Creates a cell from a line of data */
struct cell* make_cell_from_line(char* line);

/* Loads the contents of a file in a sorted list */
struct list* load_file(char* file_name);