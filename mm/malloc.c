// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	// am verificat daca size e valid
	if (size == 0)
		return NULL;
	// am declarat un pointer la structura din fisierul mem_list.c
	struct mem_list *item;
	// am inceput cautarea in lista a unei zone suficient de mare de memorie
	// de la inceputul listei
	item = mem_list_find(NULL);
	// cautarea continua pana cand zona e gasita sau se ajunge la finalul listei
	while (item != NULL) {
		// daca zona nu este suficient de mare am trecut la urmatoarea zona din
		// lista
		if (item->len < size) {
			item = mem_list_find(item->start);
		} else {
			// altfel, zona de memorie nu va mai fi disponibila, motiv pt care
			// am sters-o si i-am returnat adresa
			mem_list_del(item->start);
			return item->start;
		}
	}
	// daca nu am gasit o zona suficient de mare, am alocat una, folosind mmap
	void *nitem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	// si am adaugat-o in lista
	mem_list_add(nitem, size);
	return nitem;
	// return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	// am verificat mai intai daca nmemb si size sunt valide
	if (nmemb == 0 || size == 0) return NULL;
	// am alocat memorie pt nmemb elemente, folosind malloc
	void *result = malloc(size * nmemb);
	// daca alocarea a reusit am setat la 0 fiecare element
	if(result != NULL) {
		memset(result, 0, size * nmemb);
		return result;
	}
	return NULL;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	// daca pointerul dat este valid
	if (ptr != NULL) {
		struct mem_list *item = mem_list_find(ptr);
		// daca am gasit in lista pointerul dat
		if (item != NULL) {
			// am eliberat memoria corespunzatoare folosind munmap
			munmap(item->start, item->len);
			// si am sters elementul din lista
			mem_list_del(item->start);
		}
		return;
	}
	return;
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	if (size == 0) return NULL;
	// am cautat in lista pointerul
	struct mem_list *item = mem_list_find(ptr);
	if (item != NULL) {
		// daca l-am gasit am verificat daca zona este deja suficient de mare
		if(item->len >= size) {
			return item->start;
		}
		// daca avem nevoie de o zona mai mare
		if(size > item->len) {
			// am alocat-o, folosind malloc si am verificat daca a functionat
			void *nitem = malloc(size);
			// am copiat elementul la noua adresa
			memcpy(nitem, item->start, item->len);
			// si am eliberat zona gasita
			free(item->start);
			return nitem;
		}
	}
	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	// am verificat daca size si nmemb sunt date valide
	if (nmemb == 0 || size == 0) return NULL;
	// am apelat realloc pt dimensiunea totala
	void *result = realloc(ptr, nmemb * size);
	// am verificat daca a functionat
	if (result != NULL) {
		return result;
	}
	return NULL;
}
