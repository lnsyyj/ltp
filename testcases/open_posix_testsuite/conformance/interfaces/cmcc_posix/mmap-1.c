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

#define TNAME "cmcc_posix/mmap-1.c"


int main(void)
{
    int fd;
    int result;
    void *start;
    struct stat sb;
    char write_info[] = "This is a test file that will be used to demonstrate the use of lseek.";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char *pathname = "/tmp/cmcc_posix_mmap_1";

    // init file
    fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd < 0)
    {
        printf(TNAME " Error at open(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    result = write(fd, write_info, sizeof(write_info));
    if (result < 0)
    {
        printf(TNAME " Error at write(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    result = close(fd);
    if (result != 0)
    {
        printf(TNAME " Error at close(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    // mmap
    fd = open(pathname, O_RDWR, mode);
    if (fd < 0)
    {
        printf(TNAME " Error at open(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    result = fstat(fd, &sb);    // get file size
    if (result == -1)
    {
        printf(TNAME " Error at fstat(): %s\n", strerror(errno));
        return PTS_FAIL;
    }
    
    start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(start == MAP_FAILED)
    {
        printf(TNAME " Error at mmap(): %s\n", strerror(errno));
        return PTS_FAIL;
    }
    printf("%s\n", start); 

    result = munmap(start, sb.st_size);
    if (result == -1)
    {
        printf(TNAME " Error at munmap(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    return PTS_PASS;
}