#include "vector.h"
#include "common_test.h"

void test_vector_get_set_not_free_needed(void) {
    int a = 10, b = 20, c = 30;
    void *items[] = {&a, &b, &c};

    // No se crean copias profundas ni se libera
    Vector *v = vector_make(items, 3, NULL, NULL, NULL, false);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);

    // get
    CU_ASSERT_PTR_EQUAL(vector_get(v, 0), &a);
    CU_ASSERT_PTR_EQUAL(vector_get(v, -1), &c);

    // set (el vector solo guarda la referencia)
    int d = 99;
    vector_set(v, 1, &d);
    CU_ASSERT_PTR_EQUAL(vector_get(v, 1), &d);

    vector_destroy(v); // no libera enteros
}

void test_vector_get_set_user_ownership(void) {
    char *s1 = copy_string("alpha");
    char *s2 = copy_string("beta");
    char *s3 = copy_string("gamma");

    void *items[] = {s1, s2, s3};

    // No se crea copia profunda ni se libera(responsabilidad del usuario)
    Vector *v = vector_make(items, 3, NULL, NULL, cmp_string, false);

    CU_ASSERT_PTR_NOT_NULL(v);

    CU_ASSERT_STRING_EQUAL((char *)vector_get(v, 0), "alpha");
    CU_ASSERT_STRING_EQUAL((char *)vector_get(v, -1), "gamma");

    // set
    char *s4 = copy_string("delta");
    vector_set(v, 1, s4);
    CU_ASSERT_STRING_EQUAL((char *)vector_get(v, 1), "delta");

    vector_destroy(v); // no libera strings

    // liberar manualmente (ownership es del usuario)
    free(s1);
    free(s2);
    free(s3);
    free(s4);
}

void test_vector_get_set_structure_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);
    Person *p3 = person_create("Charlie", 20);

    void *items[] = {p1, p2, p3};

    // No se crean copias profundas, el vector libera los elementos
    Vector *v = vector_make(items, 3, free_person, copy_person, cmp_person, false);

    CU_ASSERT_PTR_NOT_NULL(v);

    CU_ASSERT_STRING_EQUAL(((Person *)vector_get(v, 0))->name, "Alice");
    CU_ASSERT_STRING_EQUAL(((Person *)vector_get(v, -1))->name, "Charlie");

    // set con liberación automática del anterior
    Person *p4 = person_create("Diana", 40);
    vector_set(v, 1, p4);
    CU_ASSERT_STRING_EQUAL(((Person *)vector_get(v, 1))->name, "Diana");

    vector_destroy(v); 
}