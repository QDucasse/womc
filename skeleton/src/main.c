#include <assert.h>
#include <time.h>

#include "llist.h"



int main(int argc, char *argv[]) {
    char* file_name;
    switch (argc) {
        case 1: 
            file_name = "medium.txt"; 
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
    end = clock();
    // print_list(l);
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
    // print_llist(ll);
    free_llist(ll);

    lltime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Construction with list took %f seconds\n", lltime);

    return 0;
}