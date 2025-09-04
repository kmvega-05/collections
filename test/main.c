#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Declaración de los tests
void test_vector_make_strings(void);
void test_vector_make_struct(void);

int main() {
    /* Inicializar registro de tests */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* Suite de tests de Vector */
    CU_pSuite vector_suite = CU_add_suite("Vector Tests", NULL, NULL);
    if (!vector_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(vector_suite, "Make with strings", test_vector_make_strings);
    CU_add_test(vector_suite, "Make with structs", test_vector_make_struct);

    /* Ejecutar tests en modo verbose */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Limpiar registro */
    CU_cleanup_registry();
    return CU_get_error();
}
