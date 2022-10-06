#include <time.h>

#include "list.h"

int main(int argc, char *argv[]) {
    struct list* l;
    l = new_list();
    print_list(l);

    struct cell* c;
    c = make_cell("Annie", "ERNAUX", "76170");
    
    push(l, c);

    print_list(l);

    free_list(l);
    return 0;
}