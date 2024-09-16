// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	/* TODO: Implement lseek(). */
	off_t new, current;
	// cazul in care descriptorul de fisier e invalid
	if (fd < 0) {
		return -1;
	}
	// offset invalid
	if (offset == -1) {
		errno = 22;
		return -1;
	}
	// valoarea lui whence nu e valida
	if (whence != SEEK_CUR && whence != SEEK_END && whence != SEEK_SET) {
		errno = 22;
		return -1;
	}
	// am obtinut pozitia curenta a cursorului
	current = syscall(8, fd, 0, SEEK_CUR);
	if(current != -1){
		// si am calculat noua pozitie, in functie de valoarea lui whence
		// deplasare relativa fata de pozitia curenta
		if (whence == SEEK_CUR) {
			new = current + offset;
		}
		// deplasare fata de sfarsitul fisierului
		if (whence == SEEK_END) {
			new = syscall(8, fd, 0, SEEK_END) + offset;
		}
		// deplasare absoluta, mutand cursorul la o alta pozitie
		if (whence == SEEK_SET) {
			new = offset;
		}
		// am setat noua pozitie a cursorului
		off_t result = syscall(8, fd, new, SEEK_SET);
		return result;
	}
	return -1;
}
