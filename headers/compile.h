#ifndef _COMPILE_H_
#define _COMPILE_H_

#include <stdbool.h>
//https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html  -- more info here
//TODO continue to write all flags
typedef enum {
    ADDRESS, 
    KERNEL_ADDRESS,
} sanitaze;

typedef enum {
    STD_99, STD_11, STD_17, STD_23
}std_compiler_v;


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

struct cur_project {
    files *files;
    libs *libs;
    warnings *warnings; //default -Wall -Werror
    bool debug;  //default nothing
    sanitaze *sanityzer;  //default nothing
    std_compiler_v version; // default -std=c17
    char *execut_line;
};

typedef struct cur_project C_setup;

//init struct cur_project and set all flags
C_setup *init_compiler(int argc, char **args);
int compile(C_setup *setup);

#endif //_COMPILE_H_
