// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	size_t i;
	// am copiat fiecare caracter din sursa in destinatie,
	// inclusiv terminatorul
	for(i = 0; i <= strlen(source); i++){
		destination[i] = source[i];
	}

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	// am copiat primele len caractere din sursa in destinatie
	size_t i;
	for(i = 0; i < len; i++){
		destination[i] = source[i];
	}
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	size_t i;
	// am retinut mai intai lungimile sirurilor in 2 variabile
	size_t dl = strlen(destination);
	size_t sl = strlen(source);
	// apoi am copiat caracterele din sursa la finalul destinatiei
	for(i = 0; i <= sl; i++){
		destination[i + dl] = source[i];
	}
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	size_t i;
	size_t dl = strlen(destination);
	// am copiat primele len caractere din sursa in destinatie
	for(i = 0; i < len; i++){
		destination[i + dl] = source[i];
	}
	// am plasat la final terminatorul de sir
	destination[i + dl] = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	size_t len1, len2, i;
	len1 = strlen(str1);
	len2 = strlen(str2);
	// cazul in care sirurile au lungimi egale
	if(len1 == len2){
		int ok = 0;
		for(i = 0; i < len1; i++){
			// cand caracterele de pe aceeasi pozitie sunt diferite
			if(str1[i] != str2[i]){
				// daca caracterul din primul sir e mai mare
				if(str1[i] > str2[i])
					return 1;
				// daca e mai mic
				else
					return -1;
				ok = 1;
			}
		}
		// daca nu s-au gasit caractere diferite
		if(ok == 0){
			return 0;
		}
	}
	// cazul in care primul sir e mai lung
	if(len1 > len2) return 1;
	// cazul in care al doilea sir e mai lung
	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
		size_t i;
		int ok = 0;
		// am comparat primele len caractere din ambele siruri
		for(i = 0; i < len; i++){
			// cand am gasit caractere diferite am verificat care sir
			// are caracterul mai mare
			if(str1[i] != str2[i]){
				if(str1[i] > str2[i])
					return 1;
				ok = 1;
			}
		}
		if(ok == 0){
			return 0;
		}
	return -1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	size_t len = strlen(str);
	size_t i;
	// am parcurs sirul si daca am gasit caracterul cautat
	// l-am returnat
	for(i = 0; i < len; i++){
		if(str[i] == c)
			return (char *)(str + i);
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	int i;
	// am parcurs sirul de la final si daca am gasit caracterul
	// l-am returnat
	for(i = strlen(str) - 1; i >= 0; i--){
		if(str[i] == c) return (char *)(str + i);
	}
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	size_t i = 0, k;
	int j = 0, ok;
	while(i < strlen(haystack)) {
		// daca am gasit primul caracter din needle in haystack
		// incep sa caut intregul sir de la pozitia i
		if(haystack[i] == needle[0]){
			ok = 0;
			j = i;
			for(k = 0; k < strlen(needle); k++){
				// daca am gasit un caracter care difera, ok devine 1
				if(haystack[i] != needle[k]){
					ok = 1;
				}
				i++;
			}
			// daca ok a ramas 0, atunci pot returna adresa inceputului
			// lui needle in haystack
			if(ok == 0)
				return (char *)(haystack + j);
			// altfel continui de la pozitia la care am ramas cu cautarea
			else
				i = j;
		}
		i++;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	size_t i = 0, k, j, l, q;
	q = strlen(haystack) - 1;
	l = strlen(needle) - 1;
	int ok;
	while(i <= q) {
		// am aplicat principiul de la strstr, doar ca am pornit
		// de la finalul ambelor siruri
		if(haystack[q - i] == needle[l]){
			ok = 0;
			j = i;
			for(k = 0; k <= l; k++){
				if(haystack[q - i] != needle[l - k]){
					ok = 1;
				}
				i++;
			}
			if(ok == 0) return (char *)(haystack + q - i + 1);
			else
				i = j;
		}
		i++;
	}
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	size_t i = 0;
	// am facut cast la char pt a putea lucra cu pointerii
	char *d = (char *)destination;
	char *s = (char *)source;
	// am copiat byte cu byte din sursa in destinatie
	while(i != num) {
		d[i] = s[i];
		i++;
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	size_t i;
	// am facut cast la char pt a putea lucra cu pointerii
	char *d = (char *)destination;
	char *s = (char *)source;
	if(d != s){
		// in acest caz, am copiat invers pentru a evita suprapunerea
		if(d > s) {
			for(i = num; i > 0; i--){
				d[i - 1] = s[i - 1];
			}
		} else {
			// altfel am copiat de la inceput
			for(i = 0; i < num; i++){
				d[i] = s[i];
			}
		}
	}
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	// am facut cast la char pt a putea lucra cu pointerii
	char *d = (char *)ptr1;
	char *s = (char *)ptr2;
	size_t i = 0;
	int ok = 0;
	while(i < num){
		// daca am gasit un caracter diferit, ok a crescut
		if(d[i] != s[i]){
			ok = 1;
		}
		i++;
	}
	// daca ok a ramas 0, atunci returnam 0
	if(ok == 0)
		return 0;
	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	size_t i = 0;
	char *s = (char *)source;
	char v = (char)value;
	// am setat primii num bytes din source la value
	while(i < num) {
		s[i] = v;
		i++;
	}
	return source;
}
