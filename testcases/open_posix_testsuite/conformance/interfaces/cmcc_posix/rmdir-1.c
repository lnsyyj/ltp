/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/rmdir-1.c"

int main(void)
{
	struct stat st = {0};
	int result;
	char *pathname = "/tmp/cmcc_posix_rmdir_1";

	if (mkdir(pathname, 0700) != 0)
	{
		return PTS_FAIL;
	}

	if (rmdir(pathname) != 0)
	{
		return PTS_FAIL;
	}
	
	return PTS_PASS;
}