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


static void insert_strings_in_ex_line(char **list, int size, char *line) {
    for(int i = 0; i < size; i++) {
        strcat(line, list[i]);
        strcat(line, " ");
    }
}

void prepare_execution_line(C_setup *setup) {
    char e_line[1024]; 
    memset(e_line, 0, 512);
    strcat(e_line, "gcc  ");
    strcat(e_line, setup->version);
    insert_strings_in_ex_line(setup->files->file, setup->files->len, e_line);
    insert_strings_in_ex_line(setup->warnings->warn, setup->warnings->len, e_line);
    insert_strings_in_ex_line(setup->libs->lib, setup->libs->len, e_line);
    insert_strings_in_ex_line(setup->sanitizer->san, setup->sanitizer->len, e_line);
    if (setup->debug) {
        strcat(e_line, "-g ");
    }
    int size = strlen(e_line);
    setup->execut_line = (char *) malloc(size);
    strcpy(setup->execut_line, e_line);


}
