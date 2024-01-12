#include "../headers/compile.h"
#include "../headers/profile.h"


//TODO for future here will be write fucntional for building enrire all project,
//for now anly runtime compiling files thet user enter
C_setup *init_compiler(int argc, char **args) {
    C_setup *setup;
    if (argc <= 1) {
        fprintf(stderr, "You din't enter any option\n Write option [help] for more information");
    }
    if (strcmp(args[1], "-pc") == 0) {
        setup = profile_create();
    }
    if (strcmp(args[1], "-p") == 0) {
        setup = profile_load(args[2]);
    } 
    return setup;
}

int compile(C_setup *setup);

//cancation all option to one line 
char *prepare_execution_line(C_setup *setup);
