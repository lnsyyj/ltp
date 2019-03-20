/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

/*
 * S_IRUSR: read permission, owner
 * S_IWUSR: write permission, owner
 * S_IRGRP: read permission, group
 * S_IROTH: read permission, others
 * 
 * O_WRONLY: Open for writing only.
 * O_CREAT: If the file exists, this flag has no effect. Otherwise, the file is created;
 * O_TRUNC: If the file exists and is a regular file, and the file is successfully opened O_RDWR or O_WRONLY, its length is truncated to 0 and the mode and owner are unchanged.
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/open-1.c"

int main(void)
{
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *pathname = "/tmp/cmcc_posix_open_1";
	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at open(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	close(fd);
	return PTS_PASS;
}