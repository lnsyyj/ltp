/*
 * Copyright (c) 2004, Bull SA. All rights reserved.
 * Created by:  lnsyyj@hotmail.com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.
 */

/*
 *Some of you have reached the point in the project where you need to read
 *the contents of a directory to handle attributes such as "ALL" and
 *"ALLUSER".   At the user-level, you can use routines such as opendir(),
 *readdir() and scandir(), which are all library routines (not system
 *calls).  These routines work if all your code is at the user level, but
 *eventually you will need to move it to the kernel level.  The following
 *program uses the system call getdents() to read the contents of a
 *directory.  See the man page for getdents() for more info.  The program
 *assumes that a directory is given on the command line as an argument.
 *Because this is a more "obscure" system call, there is not an entry for it
 *the right header file so it is necessary to include the _syscall3 entry in
 *the code to describe the parameters of the system call.
				- Craig Wills
 */

// open a directory then read and print all entries
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
// #include <linux/unistd.h>
#include <unistd.h>
#include "posixtest.h"

#define TNAME "cmcc_posix/getdents-1.c"

extern int errno;

/*
The line _syscall3(int, getdents, ...); should have been added to
/usr/src/linux/include/linux/dirent.h for users to use this systemcall.
However, it was omitted for some reason. Maybe a bug.
*/
_syscall3(int, getdents, uint, fd, struct dirent *, dirp, uint, count);

int main(void)
{
    int fd;
    struct dirent dent;
    char *pathname = "/tmp";

    if ((fd = open(pathname, O_RDONLY)) < 0) {
        fprintf(stderr, "Failed to open %s\n", pathname);
        return PTS_FAIL;
    }
    else {
        while (getdents(fd, &dent, sizeof(dent)) > 0) {
            printf("%s\n", dent.d_name);
            lseek(fd, dent.d_off, SEEK_SET);
        }
    }
    close(fd);
    return PTS_PASS;
}