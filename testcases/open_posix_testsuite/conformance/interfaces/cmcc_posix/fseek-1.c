/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/fseek-1.c"

int main(void)
{
    FILE * stream;
    long offset;
    fpos_t pos;
    char *pathname = "/tmp/cmcc_posix_fseek_1";

    stream = fopen(pathname, "w+");
    if (stream == NULL)
    {
        perror("fopen() error");
        return PTS_FAIL;
    }

    if (fseek(stream, 5, SEEK_SET) < 0)
    {
        perror("fseek() error");
        return PTS_FAIL;
    }
    printf("offset = %d\n", ftell(stream));

	rewind(stream);
    if (fgetpos(stream, &pos) != 0)
    {
    	perror("fgetpos() error");
    	return PTS_FAIL;
    }
    printf("offset = %d\n", pos);

    pos.__pos = 10;
    if (fsetpos(stream, &pos) != 0)
    {
    	perror("fsetpos() error");
    	return PTS_FAIL;
    }
    printf("offset = %d\n", ftell(stream));

    if (fclose(stream))
    {
    	perror("fclose() error");
    	return PTS_FAIL;
    }

    return PTS_PASS;
}