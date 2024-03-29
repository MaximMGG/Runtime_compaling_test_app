#ifndef _PROFILE_H_
#define _PROFILE_H_
#include "compile.h"
#include "disk_work.h"
#include <stdlib.h>
#include <stdio.h>
#include "run_util.h"

//create new profile return C_setup *
C_setup *profile_create();

//load profile from dirrectory ./local/share/runtime_c/profile_name.conf
C_setup *profile_load(char *profile_name);

//save profile in dirrectory ./local/share/runtime_c/profile_name.conf
int profile_save(C_setup *setup, char *profile_name);

//change profile setting TODO write this
C_setup *profile_change(C_setup *setup);

//sets files in files struct
int profile_set_files(C_setup *setup, char *files);

//frees all memory in setup struct
void profile_free(C_setup *setup);


#endif //_PROFILE_H_
