#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *t1, struct timespec *t2) {
    // am efectuat apel de sistem cat timp am intalnit eroarea
    while (syscall(35, t1, t2) == -1) {
        if (errno == 4) {
            // la intalnirea erorii EINTR am trecut la timpul ramas pt
            // asteptare
            t1 = t2;
        } else {
            // altfel am returnat -1 in cazul in care a aparut alta problema
            return -1;
        }
    }
    return 0;
}

unsigned int sleep(unsigned int seconds) {
    struct timespec t1, t2;
    t1.seconds = seconds;
    t1.nanoseconds = 0;
    // am initializat valorile structurii t2
    t2.seconds = 0;
    t2.nanoseconds = 0;
    while (syscall(35, &t1, &t2) == -1) {
        // daca am primit eroare si mai avem timp de asteptat, am trecut la el
        if (t2.seconds > 0 || t2.nanoseconds > 0) {
            t1 = t2;
        } else {
            return 0;
        }
    }
    return 0;
}
