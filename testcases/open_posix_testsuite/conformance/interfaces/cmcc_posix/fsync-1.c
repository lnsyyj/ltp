/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/fsync-1.c"

int main(void)
{

	int fd;
	int result;
	char write_info[] = "This is a test file that will be used to demonstrate the use of lseek.";
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *pathname = "/tmp/cmcc_posix_fsync_1";

	// init file content
	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	printf("write_info size %d\n", sizeof(write_info));
	result = write(fd, write_info, sizeof(write_info));
	printf("write result %d\n", result);
	if (result < 0)
	{
		printf(TNAME " Error at write(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	result = fsync(fd);
	if (result == -1)
	{
		printf(TNAME " Error at fsync(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	result = close(fd);
	if (result != 0)
	{
		printf(TNAME " Error at close(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	return PTS_PASS;
}