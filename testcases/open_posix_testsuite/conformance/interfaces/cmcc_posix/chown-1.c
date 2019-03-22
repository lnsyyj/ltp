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

#define TNAME "cmcc_posix/chown-1.c"

int main(void)
{
	int fd;
	int result = -1;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *pathname = "/tmp/cmcc_posix_chown_1";
	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	close(fd);

	result = chown(pathname, 99, 99);
	if (result > 0)
	{
		return PTS_FAIL;
	}
	return PTS_PASS;
}