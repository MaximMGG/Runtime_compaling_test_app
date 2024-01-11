#include "../headers/run_util.h"


#define DEF_LIST_SIZE 10

run_list *list_create() {
    run_list *list = (run_list *) malloc(sizeof(*list));
    if (list  == NULL) list_error_func(MEMORY_ERROR);
    list->list = (char **) malloc(sizeof(char *) * DEF_LIST_SIZE);
    if (list->list == NULL) list_error_func(MEMORY_ERROR);
    list->list_len = 0;

    return list;
}

int list_add(char *);

char *list_get(int pos);

int list_error_func(list_error error);
