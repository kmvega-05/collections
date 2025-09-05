#include "vector/vector.h"
#include "common/common_test.h"

void test_vector_index_of_and_contains(void) {
    // Creamos algunos enteros estáticos (no requieren free)
    int a = 10, b = 20, c = 30;
    void *items[] = {&a, &b, &c};

    Vector *v = vector_make(items, 3, NULL, NULL, cmp_int);

    // Prueba index_of
    CU_ASSERT_EQUAL(vector_index_of(v, &a), 0);
    CU_ASSERT_EQUAL(vector_index_of(v, &b), 1);
    CU_ASSERT_EQUAL(vector_index_of(v, &c), 2);

    // Prueba contains
    CU_ASSERT_TRUE(vector_contains(v, &a));
    CU_ASSERT_TRUE(vector_contains(v, &c));
    CU_ASSERT_FALSE(vector_contains(v, &(int){40}));

    vector_destroy(v);
}