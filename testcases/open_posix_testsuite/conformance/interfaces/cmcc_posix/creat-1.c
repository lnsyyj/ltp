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
 */

#include <fcntl.h>
#include <errno.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/creat-1.c"

int main(void)
{
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *filename = "/tmp/cmcc_posix_creat_1";
	fd = creat(filename, mode);
	if (fd < 0)
	{
		printf(TNAME " Error at creat(): %s\n", strerror(errno));
		return PTS_FAIL;
	}
	close(fd);
	return PTS_PASS;
}