/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/msync-1.c"

int main(void)
{

    size_t bytesWritten =0;
    int fd;
    int PageSize;
    const char text[] = "This is a test";
    char *pathname = "/tmp/cmcc_posix_msync_1";

    if ((PageSize = sysconf(_SC_PAGE_SIZE)) < 0)
    {
        perror("sysconf() Error=");
        return PTS_FAIL;
    }

    fd = open(pathname, (O_CREAT | O_TRUNC | O_RDWR), (S_IRWXU | S_IRWXG | S_IRWXO));
    if ( fd < 0 )
    {
        perror("open() error");
        return PTS_FAIL;
    }

    off_t lastoffset = lseek(fd, PageSize, SEEK_SET);
    bytesWritten = write(fd, " ", 1);
    if (bytesWritten != 1)
    {
        perror("write error.");
        return PTS_FAIL;
    }

    /* mmap the file. */
    void *address;
    int len;
    off_t my_offset = 0;
    len = PageSize;   /* Map one page */
    address = mmap(NULL, len * 5, PROT_WRITE, MAP_SHARED, fd, my_offset);

    if (address == MAP_FAILED)
    {
        perror("mmap error.");
        return PTS_FAIL;
    }
    /* Move some data into the file using memory map. */
    // (void) strcpy((char*) address, text);
    strcpy((char*) address, text);
    /* use msync to write changes to disk. */
    if (msync(address, PageSize , MS_SYNC) < 0)
    {
        perror("msync failed with error:");
        return PTS_FAIL;
    }
    else
    {
        printf("%s","msync completed successfully.");
    }
    close(fd);
    // unlink(pathname);

    return PTS_PASS;
}