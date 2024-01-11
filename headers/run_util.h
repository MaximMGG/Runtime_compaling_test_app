#ifndef _RUN_UTIL_H_
#define _RUN_UTIL_H_
#include <stdlib.h>

//list func begin--------------
typedef struct {
    char **list;
    int list_len;
} run_list;

typedef enum{
    OUT_OF_BOUD = -1, MEMORY_ERROR = -2, CREATE_LIST_ERROR = -3
}list_error;

run_list *list_create();

int list_add(char *);

char *list_get(int pos);

int list_error_func(list_error error);

//list func end----------------

#endif //_RUN_UTIL_H_
