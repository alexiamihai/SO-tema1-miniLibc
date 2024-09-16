// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	/* TODO: Implement fstat(). */
	// am verificat daca descriptorul de fisier e valid si daca nu, am
	// returnat eroarea corespunzatoare
	if (fd < 0) {
		errno = EBADF;
		return -1;
	}
	// apel de sistem, urmat de verificarea rezultatului si de setarea erorii
	int result = syscall(5, fd, st);
	if (result < 0) {
		errno = - result;
		return -1;
	}
	return result;
	//return -1;
}
