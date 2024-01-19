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


//profile create =============================================================

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
    char debug[10];
    fgets(debug, 10, stdin);
    if (debug[0] != '1' && debug[0] != '0') {
        printf("Incorrect option %d try agane\n", *debug);
        setup_debug(setup);
        return;
    }
    setup->debug = debug[0] == '1' ? 1 : 0;
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

//profile create =============================================================

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


static void map_list_helper(run_list *buf, char **target) {
    target = (char **) malloc(sizeof(char *) * buf->list_len);

    char *s;
    for(int i = 0; i < buf->list_len; i++) {
        s = list_get(buf, i);
        int size = strlen(s);
        target[i] = (char *) malloc(size);
        strcpy(target[i], s);
    }
}


static C_setup *map_setup_from_list(run_list *list) {
    C_setup *setup = (C_setup *) malloc(sizeof(C_setup));
    
    char *temp;
    run_list *buf_l = list_create();

    for(int i = 0; i < list->list_len; i++) {
        if (strcmp(list_get(list, i), "libs:") == 0) {
            i += 2;
            while(strcmp((temp = list_get(list, i)), ">") != 0) {
                list_add(buf_l, temp);
            }
            if (buf_l->list_len != 0) {
                setup->libs = (libs *) malloc(sizeof(libs));
                map_list_helper(buf_l, setup->libs->lib);
            } else {
                free(setup->libs);
                setup->libs = NULL;
            }
            list_clear(buf_l);
        } else if (strcmp(list_get(list, i), "warnings:") == 0) {
            i += 2;
            while(strcmp((temp = list_get(list, i)), ">") != 0) {
                list_add(buf_l, temp);
            }
            if (buf_l->list_len != 0) {
                setup->warnings = (warnings *) malloc(sizeof(warnings));
                map_list_helper(buf_l, setup->warnings->warn);
            } else {
                free(setup->warnings);
                setup->warnings = NULL;
            }
            list_clear(buf_l);

        } else if (strcmp(list_get(list, i), "sanitize:") == 0) {
            i += 2;
            while(strcmp((temp = list_get(list, i)), ">") != 0) {
                list_add(buf_l, temp);
            }
            if (buf_l->list_len != 0) {
                setup->sanitizer = (sanitize *) malloc(sizeof(sanitize));
                map_list_helper(buf_l, setup->sanitizer->san);
            } else {
                free(setup->sanitizer);
                setup->sanitizer = NULL;
            }
            list_clear(buf_l);

        } else if (strcmp(list_get(list, i), "version:") == 0) {
            i += 2;
            temp = list_get(buf_l, i);
            if (strcmp(temp, ">") != 0) {
                setup->version = (char *) malloc(sizeof(char) * strlen(temp));
                strcpy(setup->version, temp);
            }
            list_clear(buf_l);

        } else if (strcmp(list_get(list, i), "debug:") == 0) {
            i += 2;
            temp = list_get(buf_l, i);
            if (strcmp(temp, ">") != 0) {
                setup->debug = 1;
            } else {
                setup->debug = 0;
            }
        }
    }

    list_destroy(list);
    return setup;
}



C_setup *profile_load(char *profile_name) {
    C_setup *setup;
    run_list *list = d_get_profiles();
    run_list *pr_setup = NULL;

    for(int i = 0; i < list->list_len; i++) {
        if (strcmp(profile_name, list_get(list, i)) == 0) {
            pr_setup = d_load_profile(profile_name);
            setup = map_setup_from_list(list);

        }
    }

    if (pr_setup == NULL) {
        fprintf(stderr, "Does not have profile with that name: %s\n", profile_name);
        return NULL;
    }

    return setup;
}

int profile_set_files(C_setup *setup, char *file_buf) {
    int size;
    char **file_l = str_split(file_buf, ',', &size);
    if (size == 0) {
        fprintf(stderr, "Can't find any file");
        return -1;
    }
    setup->files = (files *) malloc(sizeof(files));
    setup->files->file = file_l;
    setup->files->len = size;
    return 0;
}


static void profile_save_helper(run_list *list, char **lib, int size, char *lib_name) {
    list_add(list, lib_name);
    list_add(list, "<");
    for(int i = 0; i < size; i++) {
        list_add(list, lib[i]);
    }
    list_add(list, ">");
}



int profile_save(C_setup *setup, char *profile_name) {
    run_list *list = list_create();
    
    if (setup->libs->lib == NULL)
        profile_save_helper(list, NULL, 0, "libs:");
    else
        profile_save_helper(list, setup->libs->lib, setup->libs->len, "libs:");

    if (setup->warnings == NULL)
        profile_save_helper(list, NULL, 0, "warnings:");
    else
        profile_save_helper(list, setup->warnings->warn, setup->warnings->len, "warnings:");

    if (setup->sanitizer == NULL)
        profile_save_helper(list, NULL, 0, "sanitize:");
    else
        profile_save_helper(list, setup->sanitizer->san, setup->sanitizer->len, "sanitize:");
    if (setup->version == NULL) 
        profile_save_helper(list, NULL, 0, "version:");
    else 
        profile_save_helper(list, &setup->version, 1, "version"); 
    if (setup->debug == 0)
        profile_save_helper(list, NULL, 0, "debug:");
    else  {
        char *deb = "-g";
        profile_save_helper(list, &deb, 1, "debug");
    }

    profile_name = str_trim(profile_name);
    d_save_profile(list, profile_name);

    return 0;
}

//TODO need to write this functional
C_setup *profile_change(C_setup *setup) {return NULL;}
