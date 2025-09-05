#include "vector.h"
#include "common_test.h"

void test_vector_make_not_free_needed(void) {
    char *items[] = {"one", "two", "three"};

    // Crear vector por referencia (no deep copy, el vector no libera los strings)
    Vector *v = vector_make((void **)items, 3, NULL, copy_string, cmp_string, false);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);

    // Validar contenido
    CU_ASSERT_STRING_EQUAL((char *)v->data[0], "one");
    CU_ASSERT_STRING_EQUAL((char *)v->data[1], "two");
    CU_ASSERT_STRING_EQUAL((char *)v->data[2], "three");

    vector_destroy(v); // No libera los strings, ownership del usuario

    // en este caso no es necesario liberar los strings porque se crearon como literales no con malloc
}

void test_vector_make_structure_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);
    Person *p3 = person_create("Charlie", 20);

    Person *items[] = {p1, p2, p3};

    // Crear vector con deep copy y free_func, el vector tiene el ownership de los datos que tienen un espacio de memoria diferentes a los originales
    Vector *v = vector_make((void **)items, 3, free_person, copy_person, cmp_person, true);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[0])->name, "Alice");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[1])->name, "Bob");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[2])->name, "Charlie");

    vector_destroy(v); // Libera automáticamente los Person del vector

    // Deberia dar bateo valgrind pq no se libreraon p1,p2 y p3 (el vector hizo copias profundas de ellos asi que no los libera)
    free_person(p1);
    free_person(p2);
    free_person(p3);
}

void test_vector_make_user_ownership(void) {
    Person *p1 = person_create("Alice", 30);
    Person *p2 = person_create("Bob", 25);
    Person *p3 = person_create("Charlie", 20);

    Person *items[] = {p1, p2, p3};

    // Crear vector por referencia, el usuario mantiene ownership
    Vector *v = vector_make((void **)items, 3, NULL, copy_person, cmp_person, false);

    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(v->size, 3);
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[0])->name, "Alice");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[1])->name, "Bob");
    CU_ASSERT_STRING_EQUAL(((Person *)v->data[2])->name, "Charlie");

    vector_destroy(v); // No libera los Person

    // Usuario debe liberar manualmente
    free_person(p1);
    free_person(p2);
    free_person(p3);
}
