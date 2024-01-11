#ifndef _RUN_UTIL_H_
#define _RUN_UTIL_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//list func begin--------------
typedef struct {
    char **list;
    int list_len;
    int max_len;
} run_list;

typedef enum{
    OUT_OF_BOUD = -1, MEMORY_ERROR = -2, CREATE_LIST_ERROR = -3
}list_error;

run_list *list_create();

int list_add(run_list *list, char *);

char *list_get(run_list *list, int pos);

int list_error_func(list_error error);

int list_remove(run_list *list, int pos);

//list func end----------------

//string func begin -----------

char **str_split(char *, char, int *size);

//string func end -------------

#endif //_RUN_UTIL_H_
