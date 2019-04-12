/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */


#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
// #include <stropts.h>
#include <sys/socket.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/ioctl-1.c"

#define NEW_STR     "Hello, Linux!!\n"
#define NEW_STR_LEN sizeof(NEW_STR)

struct ioctl_str {
    int str_len;
};

int main(void)
{
    char *pathname = "/tmp/cmcc_posix_ioctl_1";
    char *str = (char *)malloc(NEW_STR_LEN);
    int result = -1;

    memset(str, 0, NEW_STR_LEN);
    memcpy(str, NEW_STR, NEW_STR_LEN);

    struct ioctl_str str_io = {
        .str_len = NEW_STR_LEN,
    };

    printf("init str_io .str_len %d\n", str_io.str_len);
    int fd = open(pathname, O_CREAT | O_RDONLY);
    if (fd == -1)
    {
    	printf(TNAME " Error at open(): %s\n", strerror(errno));
    	return PTS_FAIL;
    }

    result = ioctl(fd, FIONREAD, &str_io);
    if (result == -1)
    {
    	printf(TNAME " Error at ioctl(): %s\n", strerror(errno));
    	return PTS_FAIL;
    }
    printf("retval = %d\n\n", result);
    printf("str_io .str_len %d\n", str_io.str_len);

    str_io.str_len = 1;
    result = ioctl(fd, FIONBIO, &str_io);
    if (result == -1)
    {
    	printf(TNAME " Error at ioctl(): %s\n", strerror(errno));
    	return PTS_FAIL;
    }
    printf("init str_io .str_len %d\n", str_io.str_len);

    result = close(fd);
    if(result == -1)
    {
    	printf(TNAME " Error at close(): %s\n", strerror(errno));
    	return PTS_FAIL;
    }

    return PTS_PASS;
}