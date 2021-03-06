/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */


#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/read-1.c"
#define INFO_LEN 71

int main(void)
{
	int fd;
	int result;
	char write_info[INFO_LEN] = "This is a test file that will be used to demonstrate the use of lseek.";
	char read_info[INFO_LEN] = {};
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *pathname = "/tmp/cmcc_posix_read_1";

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
	result = close(fd);
	if (result != 0)
	{
		printf(TNAME " Error at close(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	// read
	fd = open(pathname, O_RDONLY, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	result = read(fd, read_info, INFO_LEN);
	printf("read_info %s\n", read_info);
	if (result == -1 || result != INFO_LEN)
	{
		printf(TNAME " Error at read(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	result = close(fd);
	if (result != 0)
	{
		printf(TNAME " Error at close(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	// read lseek
	fd = open(pathname, O_RDONLY, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	result = lseek(fd, 8, SEEK_SET);
	printf("lseek result %d\n", result);
	if (result == -1)
	{
		printf(TNAME " Error at lseek(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	result = read(fd, read_info, INFO_LEN);
	printf("read_info %s\n", read_info);
	if (result == -1)
	{
		printf(TNAME " Error at read(): %s\n", strerror(errno));
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