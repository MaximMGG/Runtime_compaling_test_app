#include "../headers/profile.h"
#include <string.h>
#include <stdio.h>

#define Werror_len 3
static const char Werror[][20] = {"-Wall", "-Werror", "-Wexta"};

static void print_Werror() {
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
            return -1;
        }
        setup->warnings->warn[setup->warnings->len] = (char *) malloc(sizeof(Werror[i]));
        strcpy(setup->warnings->warn[setup->warnings->len], Werror[i]);
        setup->warnings->len++;
    }
    return 0;
}



C_setup *profile_create() {
    C_setup *setup = (C_setup *) malloc(sizeof(C_setup));




    return setup;
}
