#include <CUnit/Basic.h>
#include "../../src/vector/vector.h"
#include "../../src/common/common_test.h"

void test_vector_make_strings(void) {
    char *items[] = {"one", "two", "three"};

    Vector *v = vector_make((void **)items, 3,
                             free_string, copy_string, cmp_string);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);
    CU_ASSERT_STRING_EQUAL((char *)v->data[0], "one");
    CU_ASSERT_STRING_EQUAL((char *)v->data[1], "two");
    CU_ASSERT_STRING_EQUAL((char *)v->data[2], "three");

    vector_destroy(v);
}

void test_vector_make_struct(void) {
    Person p1 = {"Alice", 30};
    Person p2 = {"Bob", 25};
    Person p3 = {"Charlie", 20};

    Person *items[] = {&p1, &p2, &p3};

    Vector *v = vector_make((void **)items, 3,
                             free_person, copy_person, cmp_person);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[0])->name, "Alice");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[1])->name, "Bob");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[2])->name, "Charlie");

    vector_destroy(v);
}
