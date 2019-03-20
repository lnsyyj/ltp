/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */


#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/access-1.c"

int main(void)
{
	int result;
	int fd;

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXUSR;
	const char *pathname = "/tmp/cmcc_posix_access_1";
	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	close(fd);

	result = access(pathname, F_OK);
	if (result != 0)
	{
		printf(TNAME " Error at access(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	result = access(pathname, R_OK);
	if (result != 0)
	{
		printf(TNAME " Error at access(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	result = access(pathname, W_OK);
	if (result != 0)
	{
		printf(TNAME " Error at access(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	result = access(pathname, X_OK);
	if (result != 0)
	{
		printf(TNAME " Error at access(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	return PTS_PASS;
}