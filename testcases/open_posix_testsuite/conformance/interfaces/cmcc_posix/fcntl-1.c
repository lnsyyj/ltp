/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "posixtest.h"

#define TNAME "cmcc_posix/fcntl-1.c"

// int main(void)
// {
// 	int fd, var;
// 	char *pathname = "/tmp/cmcc_posix_fcntl_1";
// 	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
// 	fd = creat(pathname, mode);
// 	if (fd < 0)
// 	{
// 		printf(TNAME " Error at creat(): %s\n", strerror(errno));
// 		return PTS_FAIL;
// 	}
// 	close(fd);

// 	if((var=fcntl(pathname, F_GETFL, 0)) < 0)
// 	{
// 		printf(TNAME " fcntl file error(): %s\n", strerror(errno));
// 		return PTS_FAIL;
// 	}

// 	switch(var & O_ACCMODE)
// 	{
// 		case O_RDONLY:
// 			printf("Read only..\n");
// 			break;
// 		case O_WRONLY:
// 			printf("Write only..\n");
// 			break;
// 		case O_RDWR:
// 			printf("Read wirte..\n");
// 			break;
// 		default:
// 			break;
// 	}

// 	if (var & O_APPEND)
// 	{
// 		printf(",append\n");
// 	}

// 	if (var & O_NONBLOCK)
// 	{
// 		printf(",noblocking\n");
// 	}

// 	return PTS_PASS;
// }




int main(void) {
	char *pathname = "/tmp/cmcc_posix_fcntl_1";
    int fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);

    // append to empty file
    write(fd, "aaaaaaaaaa", 10);

    off_t cur = lseek(fd, 1, SEEK_SET);
    printf("offset after being set to 1: %ld\n", (long)cur);

    // append
    write(fd, "bbbbbbbb", 8);

    cur = lseek(fd, 0, SEEK_CUR);
    printf("offset after appending bbbbbbbb: %ld\n", (long)cur);

    cur = lseek(fd, 2, SEEK_SET);
    printf("offset after being set to 2: %ld\n", (long)cur);

    // now toggle "append mode" to FALSE
    int open_flag = fcntl(fd, F_GETFL);
    if (fcntl(fd, F_SETFL, open_flag & ~O_APPEND) == -1) {
        printf("failed to set flag\n");
        return PTS_FAIL;
    }

    cur = lseek(fd, 0, SEEK_CUR);
    printf("offset after unsetting O_APPEND: %ld\n", (long)cur);

    cur = lseek(fd, 3, SEEK_SET);
    printf("offset after being set to 3: %ld\n", (long)cur);

    // write without appending
    write(fd, "cccc", 4);

    cur = lseek(fd, 0, SEEK_CUR);
    printf("offset after writing cccc: %ld\n", (long)cur);

    // now toggle "append mode" to TRUE
    open_flag = fcntl(fd, F_GETFL);
    if (fcntl(fd, F_SETFL, open_flag | O_APPEND) == -1) {
        printf("failed to set flag\n");
        return PTS_FAIL;
    }

    cur = lseek(fd, 0, SEEK_CUR);
    printf("offset after unsetting O_APPEND: %ld\n", (long)cur);

    // append
    write(fd, "dd", 2);

    cur = lseek(fd, 0, SEEK_CUR);
    printf("offset after appending dd: %ld\n", (long)cur);

    close(fd);
    return PTS_PASS;
}