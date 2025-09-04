#include "common_test.h"
#include <stdlib.h>
#include <string.h>

void *copy_string(const void *s) {
    if (!s) return NULL;
    const char *src = s;
    char *dst = malloc(strlen(src) + 1);
    if (!dst) return NULL;
    strcpy(dst, src);
    return dst;
}

void free_string(void *s) {
    free(s);
}

int cmp_string(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

void *copy_person(const void *p) {
    if (!p) return NULL;
    const Person *src = p;
    Person *dst = malloc(sizeof(Person));
    if (!dst) return NULL;
    *dst = *src;
    return dst;
}

void free_person(void *p) {
    free(p);
}

int cmp_person(const void *a, const void *b) {
    const Person *pa = a;
    const Person *pb = b;
    return strcmp(pa->name, pb->name);
}
