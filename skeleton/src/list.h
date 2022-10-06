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

/* Allocates memory for a list structure and returns the pointer */
struct list* new_list();

/* Frees the input list and its cells */
void free_list(struct list* lst);

/* Print a cell as [fname,lname,zip] */
void print_cell(struct cell* c);

/* Print a list and its cells */
void print_list(struct list *lst);

/* Make a cell from given values */
struct cell* make_cell(char* fname, char* lname, char* zip);

/* Make a cell from an input text line */
struct cell* make_cell_from_line(char* line);

/* Push a cell on top */
void push(struct list *lst, struct cell* c);

/* Pop the head of the list in the given out pointer */
void pop(struct list* lst, struct cell* out);

/* Compare two cells, outputs 0 if equal, a negative number if a<b and positive otherwise */
int compare_cells(struct cell* a, struct cell* b);

/* Adds the cell to the list respecting alphabetical order of names/lnames */
void insert(struct list* lst, struct cell* c);

/* Loads the contents of a file in a sorted list */
struct list* load_file(char* file_name);