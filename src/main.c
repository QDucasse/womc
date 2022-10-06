#include <assert.h>

#include "list.h"



int main() {
    struct list* l;
    l = load_file("generator/out.txt");
    print_list(l);
    free_list(l);
    return 0;
}