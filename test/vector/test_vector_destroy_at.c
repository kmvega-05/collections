#include "vector.h"
#include "common/common_test.h"

void test_vector_destroy_not_free_needed(void) {
    const char *words[] = {"one", "two", "three"};
    Vector *v = vector_make((void **)words, 3, NULL, NULL, NULL);

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
    Vector *v = vector_make(arr, 2, free_person, NULL, NULL);

    vector_destroy_at(v, -1);
    CU_ASSERT_PTR_NULL(v->data[1]);
    CU_ASSERT_PTR_NOT_NULL(v->data[0]);

    vector_destroy(v);
}

void test_vector_destroy_at_user_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);

    void *arr[] = {p1, p2};
    Vector *v = vector_make(arr, 2, NULL, NULL, NULL);

    vector_destroy_at(v, -1);
    CU_ASSERT_PTR_NULL(v->data[1]);
    CU_ASSERT_PTR_NOT_NULL(v->data[0]);

    vector_destroy(v);

    free_person(p1);
    free_person(p2);
}
