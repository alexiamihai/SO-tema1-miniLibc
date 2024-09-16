#include <unistd.h>
#include <string.h>

int puts(const char *s) {
    size_t i;
    char n = '\n';
    // am scris sirul, caracter cu caracter, folosind write
    // iar in caz de eroare, am returnat -1
    for (i = 0; i < strlen(s); i ++){
        char c = s[i];
        if (write(1, &c, 1) == -1) {
            return -1;
        }
    }
    if (write(1, &n, 1) == -1) {
        return -1;
    }
    return 1;
}
