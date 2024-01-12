#include "../headers/run_util.h"

#define DEF_LIST_SIZE 10

run_list *list_create() {
    run_list *list = (run_list *) malloc(sizeof(*list));
    if (list  == NULL) list_error_func(CREATE_LIST_ERROR);
    list->list = (char **) malloc(sizeof(char *) * DEF_LIST_SIZE);
    if (list->list == NULL) list_error_func(CREATE_LIST_ERROR);
    list->list_len = 0;
    list->max_len = DEF_LIST_SIZE;

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
    if (list->list_len >= list->max_len) {
        list->max_len <<= 1;
        list->list = (char **) realloc(list->list, sizeof(char *) * list->max_len);
    }
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
        return -1;
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
    return 0;
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

void list_destroy(run_list *list) {
    for(int i = 0; i < list->list_len; i++) {
        free(list->list[i]);
    }
    free(list->list);
    free(list);
    list = NULL;
}

run_list *list_clear(run_list *list) {
    list_destroy(list);
    return list_create();
}

//string func begin -----------

static int *str_split_realloc(char **ret, int *len) {
    *len <<= 1;
    ret = (char **) realloc(ret, sizeof(char *) * *len);
    return len;
}

char **str_split(char *buf, char symbol, int *size) {
    int split_len = 10;
    int count = 0;
    char **ret = (char **) malloc(sizeof(char *) * split_len);
    char temp[128];
    char *t_p = temp;
    char *b_p = buf;
    int len = strlen(buf);

    for(int i = 0; i < len; i++) {
        if (*b_p == ' ') {
            b_p++;
            continue;
        }
        *(t_p++) = *(b_p++);
        if(*b_p == symbol || *b_p == '\0' || *b_p == '\n') {
            b_p++;
            *t_p = '\0';
            ret[count] = malloc(strlen(temp));
            strcpy(ret[count], temp);
            if (count == split_len) 
                str_split_realloc(ret, &split_len);

            t_p = temp;
        }
    }
    return ret;
}

char *str_remove_all(char *target, char symbol) {
    int size = strlen(target);
    char *res = (char *) malloc(size);
    char *t_p = target;
    char *r_p = res;

    for(int i = 0; i < size; i++) {
        if (*t_p != symbol) {
            *(r_p++) = *t_p;
        }
        t_p++;
    }
    *r_p = '\0';
    strcpy(target, res);
    free(res);
    return target;
}

//string func end -------------
