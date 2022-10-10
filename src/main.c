#include <assert.h>
#include <time.h>

#include "llist.h"



int main(int argc, char *argv[]) {
    char* file_name;
    switch (argc) {
        case 1: 
            file_name = "data/small.txt"; 
            break;
        case 2:
            file_name = argv[1];
            break;
        default: 
            printf("Wrong number of arguments, just supply the file to process (medium.txt if none).\n");
            return 1;
    }

    clock_t start, end;
    double ltime, lltime;
    
    printf("\n\n========================\n");
    printf("          list          \n");
    printf("========================\n\n");
    // list
    struct list* l;
    start = clock();
    l = load_file(file_name);
    // l = new_list();
    end = clock();
    print_list(l);
    free_list(l);

    ltime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Construction with list took %f seconds\n", ltime);


    printf("\n\n========================\n");
    printf("          llist         \n");
    printf("========================\n\n");
    // llist
    struct llist* ll;
    start = clock();
    ll = lload_file(file_name);
    end = clock();
    print_llist(ll);
    free_llist(ll);

    lltime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Construction with list took %f seconds\n", lltime);

    return 0;


    // Basic sample

    // struct list* l;
    // l = new_list();
    // print_list(l);

    // struct cell* c;
    // c = make_cell_from_values("Annie", "ERNAUX", "76170");
    
    // push(l, c);
    // print_list(l);

    // struct llist* ll;
    // ll = new_llist();
    // print_llist(ll);

    // struct lcell* lc;
    // lc = make_lcell_from_values('A', l);

    // lpush(ll, lc);
    // print_llist(ll);

    // struct cell* res;
    // res = (struct cell*) malloc(sizeof(struct cell));
    // pop(l, res);

    // print_list(l);
    // print_llist(ll);
    // free(res);

    // free_llist(ll);
    // free_list(l);
    return 0;
}