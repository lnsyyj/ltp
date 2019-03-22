/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include "posixtest.h"

#define TNAME "cmcc_posix/fstat-1.c"

int main(void)
{
    int fd;
    int result;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char *pathname = "/tmp/cmcc_posix_fstat_1";
    struct stat info;

    fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd < 0)
    {
        printf(TNAME " Error at open(): %s\n", strerror(errno));
        return PTS_FAIL;
    }

    result = fstat(fd, &info);
    if (result == -1)
    {
        printf(TNAME " Error at stat(): %s\n", strerror(errno));
        return PTS_FAIL;
    }
    close(fd);

    printf("File type;                  ");
 
    switch(info.st_mode & S_IFMT)
    {
        case S_IFBLK:   printf("block device\n");       break;
        case S_IFCHR:   printf("character device\n");   break;
        case S_IFDIR:   printf("directory\n");          break;
        case S_IFIFO:   printf("FIFO pipe\n");          break;
        case S_IFLNK:   printf("symlink\n");            break;
        case S_IFREG:   printf("regular file\n");       break;
        case S_IFSOCK:  printf("socket\n");             break;
        default:        printf("unknown\n");            break;
    }
 
    printf("I-node number:              %ld\n", (long)info.st_ino);
    printf("Mode:                       %lo(octal)\n",
            (unsigned long)info.st_mode);
    printf("Link count:                 %ld\n", (long)info.st_nlink);
    printf("Ownership:                  UID=%ld GID=%ld\n",
            (long)info.st_uid, (long)info.st_gid);
 
    printf("Preferred I/O block size:   %ld bytes\n",
            (long) info.st_blksize);
    printf("File size:                  %lld bytes\n",
            (long long) info.st_size);
    printf("Blocks allocated:           %lld\n",
            (long long) info.st_blocks);
 
    printf("Last status change:         %s", ctime(&info.st_ctime));
    printf("Last file access:           %s", ctime(&info.st_atime));
    printf("Last file modification:     %s", ctime(&info.st_mtime));
 
    return PTS_PASS;
}