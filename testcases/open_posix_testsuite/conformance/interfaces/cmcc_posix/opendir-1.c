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

#include "posixtest.h"

#define TNAME "cmcc_posix/opendir-1.c"


int main(void)
{
    DIR * dir;
    struct dirent * ptr;
    char *pathname = "/tmp";
    dir = opendir(pathname);
    if (dir == NULL)
    {
    	return PTS_FAIL;
    }

    while((ptr = readdir(dir)) != NULL)
    {
        printf("d_name : %s\n", ptr->d_name);
    }

    if(closedir(dir) != 0)
    {
    	return PTS_FAIL;
    }

    return PTS_PASS;
}