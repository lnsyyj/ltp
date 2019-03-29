/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <unistd.h>

#include "posixtest.h"

#define TNAME "cmcc_posix/chdir-1.c"


int main(void)
{
    int result;
    char *pathname = "/tmp";
    if (chdir(pathname) != 0)
    {
        return PTS_FAIL;
    }
    printf("current working directory: %s\n", getcwd(NULL, NULL));

    return PTS_PASS;
}