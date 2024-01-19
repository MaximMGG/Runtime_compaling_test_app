#ifndef _RUN_UTIL_H_
#define _RUN_UTIL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// list func begin--------------
typedef struct {
  char **list;
  int list_len;
  int max_len;
} run_list;

typedef enum {
  OUT_OF_BOUD = -1,
  MEMORY_ERROR = -2,
  CREATE_LIST_ERROR = -3
} list_error;

run_list *list_create();

int list_add(run_list *list, char *);

char *list_get(run_list *list, int pos);

int list_error_func(list_error error);

int list_remove(run_list *list, int pos);

void list_destroy(run_list *list);

run_list *list_clear(run_list *list);

// list func end----------------

// string func begin -----------

char **str_split(char *, char, int *size);

// removing all symbols in char
char *str_remove_all(char *target, char symbol);

//appent to end of string sourse part (need the sourse be allocated string)
char *str_append(char *sourse, char *part);
    
//trim the str delete last char if '\n' delete first and last chars if they not letter
char *str_trim(char *str);

// string func end -------------

#endif //_RUN_UTIL_H_
