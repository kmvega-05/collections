#include "vector.h"
#include "common_test.h"

void test_vector_make_not_free_needed(void) {

    char *items[] = {"one", "two", "three"};

    // Crear vector usando callbacks de string
    Vector *v = vector_make((void **)items, 3, NULL, copy_string, cmp_string);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);

    // Validar contenido
    CU_ASSERT_STRING_EQUAL((char *)v->data[0], "one");
    CU_ASSERT_STRING_EQUAL((char *)v->data[1], "two");
    CU_ASSERT_STRING_EQUAL((char *)v->data[2], "three");

    vector_destroy(v);

}

void test_vector_make_structure_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);
    Person *p3 = person_create("Charlie", 20);

    Person *items[] = {p1, p2, p3};

    Vector *v = vector_make((void **)items, 3, free_person, copy_person, cmp_person);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[0])->name, "Alice");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[1])->name, "Bob");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[2])->name, "Charlie");

    vector_destroy(v);
}

void test_vector_make_user_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);
    Person *p3 = person_create("Charlie", 20);

    Person *items[] = {p1, p2, p3};

    Vector *v = vector_make((void **)items, 3, NULL, copy_person, cmp_person);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[0])->name, "Alice");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[1])->name, "Bob");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[2])->name, "Charlie");

    vector_destroy(v);

    free_person(p1);
    free_person(p2);
    free_person(p3);

}