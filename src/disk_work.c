#include "../headers/disk_work.h"
#include <stdbool.h>


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


run_list *d_get_profiles() {
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

int d_add_profile_to_conf(char *pr_name) {
    FILE *f = fopen(path_to_conf, "a");

    if (f == NULL) {
        fprintf(stderr, "Can't open file %s\n", path_to_conf);
        return -1;
    }

    if(fputs(pr_name, f)) {
        fclose(f);
        return 0;
    }
    fclose(f);
    return -1;
}


int d_save_profile(run_list *list, char *pr_name) {
    char buf[164];    
    strcpy(buf, path_to_dir);
    strcat(buf, "/");
    strcat(buf, pr_name);
    FILE *f = fopen(buf, "w");

    if(f == NULL) {
        fprintf(stderr, "Path %s does not exist\n", buf);
    }
    for(int i = 0; i < list->list_len; i++) {
        // fputs(list_get(list, i), f);
        fprintf(f, "%s\n", list_get(list, i));
    }
    fclose(f);
    return 0;
}

run_list *d_load_profile(char *pr_name) {
    run_list *list = list_create();
    FILE *f = fopen(path_to_conf, "r");


    char *buf = (char *) malloc(sizeof(char) * 64);
    while(!feof(f)) {
       fgets(buf, 64, f); 
       list_add(list, str_remove_all(buf, '\n'));
    }
    fclose(f);

    return list;
}

run_list *d_read_dir(char *dir_name) {
    run_list *list = list_create();

    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        fprintf(stderr, "Can't read dirrectory %s\n", dir_name);
        return NULL;
    }

    struct dirent *dirr;
    while((dirr = readdir(dir)) != NULL) {
        list_add(list, dirr->d_name);
    }

    return list;
}

static bool file_is_c(char *file) {
    int len = strlen(file);
    if ((*file + (len - 2)) == '.' && (*file + (len - 1)) == 'c') {
        return true;
    }
    return false;
}

static bool file_is_dir(char *file) {
    if (strcmp(file, "..") == 0 || strcmp(file, ".") == 0) {
        return false;
    }
    DIR *dir = opendir(file);
    if (dir != NULL) {
        return true;
    }

    return false;
}

static run_list *collect_c_file(run_list *list_c, run_list *cur_dir) {
    for(int i = 0; i < cur_dir->list_len; i++) {
        char *file = list_get(cur_dir, i);
        if (file_is_c(file)) {
            list_add(list_c, file);
        } if (file_is_dir(file)) {

        }

    }
}


run_list *scan_dir_tree() {
    run_list *list_c = list_create();
    char cur_dir[128];
    getcwd(cur_dir, 128);
    bool tree_dir = true;
    

    return list_c;
}
