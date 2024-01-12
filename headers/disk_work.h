#ifndef _DISK_WORK_H_
#define _DISK_WORK_H_
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "run_util.h"



//create directory and config file if not exist
int setup_dir_and_conf();

//return list of all profiles
run_list *d_get_profiles();

//add profile in profile.conf file
int d_add_profile_to_conf(char *pr_name);

//save profile in runcomp_c dir, create new file with settings
int d_save_profile(run_list *list, char *pr_name);

//load profile from dirrectory
run_list *d_load_profile(char *pr_name);


#endif //_DISK_WORK_H_


/*
 libs:
    <
    -lpq
    -lcurs
    >
 warnings:   
    <
    -Wall
    -Wextra
    >
 sanitize:
    <
    >
 version:
    <
    -std=11
    >
 debug:
    <
    -g
    >
 *
 *
*/
