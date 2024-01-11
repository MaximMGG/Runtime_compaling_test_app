#ifndef _COMPILE_H_
#define _COMPILE_H_

#include <stdbool.h>
//https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html  -- more info here
typedef enum {
    
} sanitaze;



struct cur_project {
    char **files;
    unsigned int file_count;
    char **libs;
    char **warnings;
    bool debug;
    char **sanityzer;
};


#endif //_COMPILE_H_
