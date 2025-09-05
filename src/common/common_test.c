#include "common_test.h"
#include <stdlib.h>

static char *my_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy) memcpy(copy, s, len);
    return copy;
}

void *copy_string(const void *s) {
    return my_strdup((const char *)s);
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
    dst->name = my_strdup(src->name);
    dst->age  = src->age;
    return dst;
}

void free_person(void *p) {
    if (!p) return;
    Person *person = (Person *)p;
    free(person->name);  // liberar el nombre
    free(person);        // liberar la estructura
}


int cmp_person(const void *a, const void *b) {
    const Person *pa = a;
    const Person *pb = b;
    return strcmp(pa->name, pb->name);
}

Person *person_create(const char *name, int age) {
    Person *p = (Person *)malloc(sizeof(Person));
    if (!p) return NULL;
    p->name = my_strdup(name);
    p->age = age;
    return p;
}

int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);  // devuelve 1, 0 o -1
}
