#include "../headers/disk_work.h"


#define DIR_PATH "/home/%s/.local/share/runtime_c"
#define CONF_PATH "/profile.conf"
static char path_to_dir[128];
static char path_to_conf[168];

int setup_dir_and_conf() {
   char *user_name = getlogin(); 
   char buf[168];
   char mkdirbuf[128];
   char *fmt = "mkdir -p %s";
   snprintf(buf, 168, DIR_PATH, user_name);
   strcpy(path_to_dir, buf);
   snprintf(mkdirbuf, 128, fmt, buf);
   strcpy(path_to_conf, mkdirbuf);
   strcat(buf, CONF_PATH);

   FILE *f = fopen(buf, "r");
   if (f == NULL) {
        f = fopen(buf, "w");
   }
   fclose(f);

   return 0;
}


run_list *get_profiles() {
    FILE *f = fopen(path_to_conf, "r");
    
    if (f == NULL) {
        fprintf(stderr, "Can't open file %s\n", path_to_conf);
    }

    run_list *list = list_create();

    char *buf = (char *) malloc(sizeof(char) * 64);
    while(!feof(f)) {
        fgets(buf, 64, f);
        buf = str_remove_all(buf, '\n');
        list_add(list, buf);
    }
    return list;
}

char *str_remove_all(char *target, char symbol) {
    int size = strlen(target);
    char *res = (char *) malloc(size);
    char *t_p = target;
    char *r_p = res;

    for(int i = 0; i < size; i++) {
        if (*t_p != symbol) {
            *(r_p++) = *t_p;
        }
        t_p++;
    }
    *r_p = '\0';
    strcpy(target, res);
    free(res);
    return target;
}
