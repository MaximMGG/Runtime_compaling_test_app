#include "../headers/compile.h"
#include "../headers/profile.h"




//TODO for future here will be write fucntional for building enrire all project,
//for now anly runtime compiling files thet user enter
//


//TODO need to finish this function
static int profile_option(C_setup *setup) {
    puts("Enter: 1. For saving profile.\n2. For add files.\n3. For execute entire dirrectory");
    int answer;
    scanf("%d", &answer);
    if (answer == 1)  {
        puts("Enter name of profile");
        char profile_name[64];
        fgets(profile_name, 64, stdin);
        profile_save(setup, profile_name);
    }

    return 0;
}

#define GCC_ "gcc %s"
#define GCC_G "gcc %s -g"

static void fust_execution(bool g) {
   run_list *list_c = scan_dir_tree(); 
   char buf[512];
   memset(buf, 0, 512);
   for (int i = 0; i < list_c->list_len; i++) {
        strcat(buf, list_get(list_c, i));
        strcat(buf, " ");
   }
   char e_buf[556];
   if (g)
       snprintf(e_buf, 556, GCC_G, buf);
   else 
       snprintf(e_buf, 556, GCC_, buf);

   system(e_buf);
}

C_setup *init_compiler(int argc, char **args) {
    C_setup *setup;
    setup_dir_and_conf();
    if (argc <= 1) {
        fprintf(stderr, "You din't enter any option\n Write option [help] for more information");
    }
    if (strcmp(args[1], "-pc") == 0) {
        puts("Ok, lets create profile");
        setup = profile_create();
        char buf[64];
        printf("Enter profile name: ");
        fgets(buf, 64, stdin);
        d_add_profile_to_conf(buf);
        profile_save(setup, buf);
    } else if (strcmp(args[1], "-p") == 0) {
        setup = profile_load(args[2]);
    } else if (strcmp(args[1], "-e") == 0) {
        setup = (C_setup *) malloc(sizeof(C_setup));
        if (args[2] != NULL) {
            setup->execut_line = (char *) malloc(strlen(args[2]));
            strcpy(setup->execut_line, args[2]);
        } else {
            fprintf(stderr, "Can't find executable info in arguments, try age : f.e. -e gcc test.c -g");
            return NULL;
        }
        compile(setup);
    } else if (strcmp(args[1], "-fe") == 0) {
        fust_execution(false); 
    } else if (strcmp(args[1], "-feg") == 0) {
        fust_execution(true); 
    } else {
        fprintf(stderr, "Unnown flag, pleare write [help] for more information");
        return NULL;
    }
    return setup;
}


int compile(C_setup *setup) {
    int check = 0;
    if (system(setup->execut_line)) return 0;



    return -1;
}


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
