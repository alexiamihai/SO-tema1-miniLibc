// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	// am declarat lista pentru argumente si am initializat-o
	va_list arguments;
	va_start(arguments, flags);
	mode_t mode;
	int fd;
	// am verificat daca utilizatorul a ales sa creeze fisierul
	// si am obtinut modul in care acesta trebuie creat din lista de argumente
	if(flags & O_CREAT) {
		mode = va_arg(arguments, mode_t);
	}
	fd = syscall(2, filename, flags, mode);
	// am verificat rezultatul syscall-ului si in caz de eroare,
	// am setat codul acesteia
	if(fd < 0) {
		errno = -fd;
	}
	va_end(arguments);
	// am returnat descriptorul fisierului
	if(fd > 0)
		return fd;
	else
		return -1;
}
