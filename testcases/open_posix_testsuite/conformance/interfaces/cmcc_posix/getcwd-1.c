/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <limits.h>

#include "posixtest.h"

#define TNAME "cmcc_posix/getcwd-1.c"

int main(void)
{

    char cwd[PATH_MAX];
    char *pathname = "/tmp";
    
    if (chdir(pathname) != 0)
    {
        return PTS_FAIL;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
         return PTS_FAIL;
    }

    return PTS_PASS;
}