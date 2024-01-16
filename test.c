#include <stdio.h>
#include <unistd.h>
#include "headers/run_util.h"
#include "headers/disk_work.h"


int main() {
    run_list *list = scan_dir_tree();

    for(int i = 0; i < list->list_len; i++) {
        printf("%s\n", list_get(list, i));
    }

    return 0;
}
