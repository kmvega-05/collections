#ifndef COMMON_TEST_H
#define COMMON_TEST_H

#include "../vector/vector.h"

// Funciones auxiliares para tests
void *copy_string(const void *s);
void free_string(void *s);
int cmp_string(const void *a, const void *b);


// Estructura de ejemplo para tests con tipos definidos por el usuario
typedef struct {
    char name[20];
    int age;
} Person;

// Funciones auxiliares para Person
void *copy_person(const void *p);
void free_person(void *p); 
int cmp_person(const void *a, const void *b);

#endif // COMMON_TEST_H
