// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	/* TODO: Implement ftruncate(). */
	// am verificat mai intai daca descriptorul de fisier
	// si lungimea sunt valide
	if (length < 0) return -1;
	if (fd < 0) {
		errno = EBADF;
		return -1;
	}
	// am facut apel de sistem si am verificat daca a functionat
	int result = syscall(77, fd, length);
	if (result < 0) {
		errno = -result;
		return -1;
	}
	return result;
	//return -1;
}
