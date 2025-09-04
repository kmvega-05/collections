#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Declaración de los tests
void test_vector_make_not_free_needed(void);
void test_vector_make_structure_ownership(void);
void test_vector_make_user_ownership(void);

void test_vector_destroy_not_free_needed(void);
void test_vector_destroy_at_structure_ownership(void);
void test_vector_destroy_at_user_ownership(void);

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

    CU_add_test(vector_suite, "Make no free", test_vector_make_not_free_needed);
    CU_add_test(vector_suite, "Make with structure ownership", test_vector_make_structure_ownership);
    CU_add_test(vector_suite, "Make with user ownership", test_vector_make_user_ownership);
    
    CU_add_test(vector_suite, "Destroy At - no free", test_vector_destroy_not_free_needed);
    CU_add_test(vector_suite, "Destroy At - with structure ownership", test_vector_destroy_at_structure_ownership);
    CU_add_test(vector_suite, "Destroy At - with user ownership", test_vector_destroy_at_user_ownership);

    /* Ejecutar tests en modo verbose */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Limpiar registro */
    CU_cleanup_registry();
    return CU_get_error();
}
