/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/link-1.c"

int main(void)
{
	int fd;
	int result;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *pathname = "/tmp/cmcc_posix_link_1";
	char *newpathname = "/tmp/cmcc_posix_link_1_new";
	struct stat info;

	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	close(fd);

	result = link(pathname, newpathname);
	if (result == -1)
	{
		printf(TNAME " Error at link(): %s\n", strerror(errno));
		return PTS_FAIL;
	}

	return PTS_PASS;
}