#include "../headers/profile.h"
#include <string.h>
#include <stdio.h>





#define Werror_len 3
static const char Werror[][20] = {"-Wall", "-Werror", "-Wexta"};
#define Fsanitize_len 5
static const char Fsanitize[][64] = {
                                    "-fsanitize=address", 
                                    "-fsanitize=address", 
                                    "-fsanitize=kernel-address",
                                    "-fsanitize=thread",
                                    "-fsanitize=pointer-compare"
                                    };

#define Comp_version_len 5
static const char Comp_version[][16] = {"-std=99", "-std=11", "-std=17", "-std=20", "-std=23"};

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
            setup_warning(setup);
            return 0;
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

static void print_sanitize() {
    puts("Sanitize options: enter 1, 3, 2 or 2, or 1, 5");
    for(int i = 0; i < Fsanitize_len; i++) {
        printf("%d -> %s\n", i + 1, Fsanitize[i]);
    } 
}


static int setup_sanitize(C_setup *setup) {
    print_sanitize();
    char temp[32];
    fgets(temp, 32, stdin);
    int size = 0;
    char **sanitizes = str_split(temp, ',', &size);
    setup->sanitizer = (sanitize *) malloc(sizeof(sanitize *));
    setup->sanitizer->san = (char **) malloc(sizeof(char *) * size);
    for(int i = 0; i < size; i++ ) {
        int c = atoi(sanitizes[i]);
        if (c > Fsanitize_len || c < 1) {
            printf("Dot't have sanitize option with this number %d\n", c);
            free(setup->sanitizer->san);
            free(setup->sanitizer);
            setup_sanitize(setup);
            return 0;
        }
        setup->sanitizer->san[i] = (char *) malloc(strlen(Fsanitize[c - 1]));
        strcpy(setup->sanitizer->san[i], Fsanitize[c - 1]);
    }
    return 0;
}


static void print_comp_v() {
    puts("Compiler versions: enter onely one option");
    for(int i = 0; i < Comp_version_len; i++) {
        printf("%d -> %s\n", i + 1, Comp_version[i]);
    }
}

static void setup_c_version(C_setup *setup) {
    print_comp_v();
    int version;
    scanf("%d", &version);
    if (version > Comp_version_len || version < 1) {
        printf("Don't have option with this number %d try agane", version);
        setup_c_version(setup);
        return;
    }
    setup->version = (char *) malloc(strlen(Comp_version[version - 1]));
    strcpy(setup->version, Comp_version[version - 1]);
}

static void setup_debug(C_setup *setup) {
    puts("Enter 1 if you need to include (-g) debug option, or 0");
    int debug;
    scanf("%d", &debug);
    if (debug > 1 || debug < 0) {
        printf("Incorrect option %d try agane\n", debug);
        setup_debug(setup);
        return;
    }
    setup->debug = debug;
}


C_setup *profile_create() {
    int err = 0;
    C_setup *setup = (C_setup *) malloc(sizeof(C_setup));
    setup->sanitizer = NULL;
    setup->libs = NULL;
    setup->files = NULL;
    setup->warnings = NULL;
    setup->execut_line = NULL;

    err = setup_warning(setup);
    setup_libs(setup);
    err = setup_sanitize(setup);
    setup_c_version(setup);
    setup_debug(setup);
    

    return setup;
}


void profile_free(C_setup *setup) {
    if (setup->execut_line != NULL) {
        free(setup->execut_line);
    }
    if (setup->warnings != NULL) {
        for(int i = 0; i < setup->warnings->len; i++) {
            free(setup->warnings->warn[i]);
        }
        free(setup->warnings->warn);
        free(setup->warnings);
        setup->warnings = NULL;
    }
    if (setup->files != NULL) {
        for(int i = 0; i < setup->files->len; i++) {
            free(setup->files->file[i]);
        }
        free(setup->files->file);
        free(setup->files);
        setup->files = NULL;
    }
    if (setup->sanitizer != NULL) {
        for(int i = 0; i < setup->sanitizer->len; i++) {
            free(setup->sanitizer->san[i]);
        }
        free(setup->sanitizer->san);
        free(setup->sanitizer);
        setup->sanitizer = NULL;
    }
    if (setup->libs != NULL) {
        for(int i = 0; i < setup->libs->len; i++) {
            free(setup->libs->lib[i]);
        }
        free(setup->libs->lib);
        free(setup->libs);
        setup->libs = NULL;
    }
    free(setup);
}

