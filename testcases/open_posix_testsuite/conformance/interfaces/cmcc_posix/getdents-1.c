/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <errno.h>

#include "posixtest.h"
#define TNAME "cmcc_posix/getdents-1.c"

struct linux_dirent
{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

#define BUF_SIZE 1024*1024*5

int main(void)
{
    int fd, nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    int bpos;
    char d_type;
    char *pathname = "/tmp";

    fd = open(pathname, O_RDONLY | O_DIRECTORY);
    if (fd == -1)
    {
        printf(TNAME " Error at open(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    for ( ; ; )
    {
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == -1)
        {
            printf(TNAME " Error at getdents(): %s\n", strerror(errno));
            return PTS_FAIL;
        }

        if (nread == 0)
        {
            break;
        }

        for (bpos = 0; bpos < nread;)
        {
            d = (struct linux_dirent *) (buf + bpos);
            d_type = *(buf + bpos + d->d_reclen - 1);
            if( d->d_ino != 0 && d_type == DT_REG )
            {
                printf("%s\n", (char *)d->d_name );
            }
            bpos += d->d_reclen;
        }
    }

    return PTS_PASS;
}