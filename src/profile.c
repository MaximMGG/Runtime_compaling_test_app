#include "../headers/profile.h"
#include <string.h>
#include <stdio.h>

#define Werror_len 3
static const char Werror[][20] = {"-Wall", "-Werror", "-Wexta"};
static const char Fsanitize[][64] = {
                                    "-fsanitize=address", 
                                    "-fsanitize=address", 
                                    "-fsanitize=kernel-address",
                                    "-fsanitize=thread",
                                    "-fsanitize=pointer-compare"
                                    };



static void print_Werror() {
    puts("Suppresss Warnings: enter f.e. 1, 2, 5 or 1, 2 or 2");
    for(int i = 0; i < Werror_len; i++) {
        printf("%d -> %s\n", i + 1, Werror[i]);        
    }
}

static int setup_warning(C_setup *setup) {
    char buf[64];
    print_Werror();
    fgets(buf, 64, stdin);
    int size = 0;
    char **error = str_split(buf, ',', &size);
    setup->warnings = (warnings *) malloc(sizeof(warnings *));
    setup->warnings->warn = (char **) malloc(sizeof(char *) * size);
    setup->warnings->len = 0;
    for(int i = 0; i < size; i++) {
        int c = atoi(error[i]);
        c--;
        if (c >= Werror_len || c < 0) {
            printf("Do not have option with this nomber - %d\n", c + 1);
            free(setup->warnings->warn);
            free(setup->warnings);
            return -1;
        }
        setup->warnings->warn[setup->warnings->len] = (char *) malloc(sizeof(Werror[i]));
        strcpy(setup->warnings->warn[setup->warnings->len], Werror[i]);
        setup->warnings->len++;
    }
    return 0;
}

static char **map_lib(char **n_libs, int size) {
    char **map_lib = (char **) malloc(sizeof(char *) * size);

    for(int i = 0; i < size; i++) {
        map_lib[i] = (char *) malloc(strlen(n_libs[i]) + 2);
        map_lib[i][0] = '-';
        map_lib[i][1] = 'l';
        strcpy(&map_lib[i][2], n_libs[i]);
        free(n_libs[i]);
    }
    free(n_libs);

    return map_lib;
}

static int setup_libs(C_setup *setup) {
    puts("Enter libs using in your project f.e. using libcurl just enter curl if libncurses \
            just ncurses");
    char temp[128];
    fgets(temp, 128, stdin);
    int size = 0;
    char **libs_c = str_split(temp, ',', &size);
    libs_c = map_lib(libs_c, size);
    setup->libs = (libs *) malloc(sizeof(libs *));
    for(int i = 0; i < size; i++) {
        setup->libs->lib[i] = (char *) malloc(sizeof(libs_c[i]));
        strcpy(setup->libs->lib[i], libs_c[i]);
    }
    setup->libs->len = size;

    return 0;
}



//TODO write this func for libs, sanitaze
C_setup *profile_create() {
    int err = 0;
    C_setup *setup = (C_setup *) malloc(sizeof(C_setup));
    err = setup_warning(setup);
    if (err < 0) {
        free(setup);
        profile_create();
    }
    setup_libs(setup);

    return setup;
}
