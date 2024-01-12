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
run_list *get_profiles();



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
