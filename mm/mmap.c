// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	/* TODO: Implement mmap(). */
	// apel de sistem, urmat de verificarea rezultatului si de setarea erorii
	// daca este cazul
	long result = syscall(9, addr, length, prot, flags, fd, offset);
	if(result > 0) {
		return (void *)result;
	}
	errno = -result;
	return MAP_FAILED;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	// apel de sistem, urmat de verificarea rezultatului si de setarea erorii
	// daca este cazul
	long result = syscall(25, old_address, old_size, new_size, flags);
	if(result > 0) {
		return (void *)result;
	}
	errno = -result;
	return MAP_FAILED;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	// apel de sistem, urmat de verificarea rezultatului si de setarea erorii
	// daca este cazul
	long result = syscall(11, addr, length);
	if(result > 0) {
		return result;
	}
	errno = -result;
	return -1;
}
