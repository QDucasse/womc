#include <assert.h>
#include <time.h>

#include "llist.h"



int main() {
    clock_t start, end;
    double ltime, lltime;
    
    printf("\n\n========================\n");
    printf("          list          \n");
    printf("========================\n\n");
    // list
    struct list* l;
    start = clock();
    l = load_file("data/out.txt");
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
    ll = lload_file("data/out.txt");
    end = clock();
    // print_llist(ll);
    free_llist(ll);

    lltime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Construction with list took %f seconds\n", lltime);

    return 0;
}