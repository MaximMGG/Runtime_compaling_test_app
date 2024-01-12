#ifndef _COMPILE_H_
#define _COMPILE_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html  -- more info here
//TODO continue to write all flags


typedef struct {
    char **warn;
    int len;
} warnings;

typedef struct {
    char **file;
    int len;
}files;

typedef struct {
    char **lib;
    int len;
} libs;

typedef struct {
    char **san;
    int len;
} sanitize;


struct cur_project {
    files *files;
    libs *libs;
    warnings *warnings; //default -Wall -Werror
    bool debug;  //default nothing
    sanitize *sanitizer;  //default nothing
    char *version; // default -std=c17
    char *execut_line;
};

typedef struct cur_project C_setup;

//init struct cur_project and set all flags
C_setup *init_compiler(int argc, char **args);
int compile(C_setup *setup);

//cancation all option to one line 
void prepare_execution_line(C_setup *setup);


#endif //_COMPILE_H_
