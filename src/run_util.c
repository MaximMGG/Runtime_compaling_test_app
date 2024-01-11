#include "../headers/run_util.h"

#define DEF_LIST_SIZE 10

run_list *list_create() {
    run_list *list = (run_list *) malloc(sizeof(*list));
    if (list  == NULL) list_error_func(CREATE_LIST_ERROR);
    list->list = (char **) malloc(sizeof(char *) * DEF_LIST_SIZE);
    if (list->list == NULL) list_error_func(CREATE_LIST_ERROR);
    list->list_len = 0;

    return list;
}

int list_add(run_list *list, char *line) {
    int size = strlen(line);
    list->list[list->list_len] = (char *) malloc(sizeof(char) * size);
    strcpy(list->list[list->list_len], line);

    if(list->list[list->list_len] == NULL) {
        list_error_func(MEMORY_ERROR);
        return -1;
    }
    list->list_len++;

    return 0;
}

char *list_get(run_list *list, int pos) {
    if (pos >= list->list_len) {
        list_error_func(OUT_OF_BOUD);
        return NULL;
    }
    return list->list[pos];
}

int list_remove(run_list *list, int pos) {
    if (pos >= list->list_len) {
        list_error_func(OUT_OF_BOUD);
        return NULL;
    }

    if (pos == list->list_len - 1) {
        free(list->list[pos]);
        list->list[pos] = NULL;
        list->list_len--;
        return 0;
    }
    
    free(list->list[pos]);
    list->list_len--;

    for(int i = pos; i < list->list_len - 1; i++) {
        list->list[i] = list->list[i + 1];
    }


}

int list_error_func(list_error error) {
    switch(error) {
        case OUT_OF_BOUD:
            fprintf(stderr, "Out of bound error pos more then len of list\n");
            break;
        case MEMORY_ERROR:
            fprintf(stderr, "Memory allocation error, cannot add new value\n");
            break;
        case CREATE_LIST_ERROR:
            fprintf(stderr, "Creation list error\n");
            break;
    }
    return 0;
}
