#include "vector.h"
#include "common_test.h"

void test_vector_destroy_not_free_needed(void) {
    const char *words[] = {"one", "two", "three"};
    // No se crean copias profundas ni se libera
    Vector *v = vector_make((void **)words, 3, NULL, NULL, NULL, false);

    vector_destroy_at(v, 0);
    CU_ASSERT_PTR_NULL(v->data[0]);
    CU_ASSERT_PTR_NOT_NULL(v->data[1]);

    vector_destroy_at(v, -1);
    CU_ASSERT_PTR_NULL(v->data[2]);
    CU_ASSERT_PTR_NOT_NULL(v->data[1]);

    vector_destroy(v);
}

void test_vector_destroy_at_structure_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);

    void *arr[] = {p1, p2};
    // Se crean copias profundas de las personas y el vector libera dichas copias(el usuario debe liberar las originales)
    Vector *v = vector_make(arr, 2, free_person, copy_person, cmp_person, true);

    vector_destroy_at(v, -1);
    CU_ASSERT_PTR_NULL(v->data[1]);
    CU_ASSERT_PTR_NOT_NULL(v->data[0]);

    vector_destroy(v); // Libera automáticamente el restante

    free_person(p1);
    free_person(p2);
}

void test_vector_destroy_at_user_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);

    void *arr[] = {p1, p2};
    // No se crean copias profundas ni se libera(responsabilidad del usuario)
    Vector *v = vector_make(arr, 2, NULL, copy_person, cmp_person, false);

    vector_destroy_at(v, -1);
    CU_ASSERT_PTR_NULL(v->data[1]);
    CU_ASSERT_PTR_NOT_NULL(v->data[0]);

    vector_destroy(v);

    free_person(p1);
    free_person(p2);
}
