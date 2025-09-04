#include "vector.h"

Vector *vector_make(void **items, size_t size, free_func free, copy_func copy, cmp_func cmp) {
    // Reservar memoria para la estructura
    Vector *v = malloc(sizeof(Vector));
    if (!v) return NULL;

    // Inicializar campos
    v->size = size;
    v->free = free;
    v->copy = copy;
    v->cmp  = cmp;

    // Reservar memoria para los punteros de datos
    v->data = calloc(size, sizeof(void *));
    if (!v->data) {
        free(v);
        return NULL;
    }

    // Inicializar con elementos si se proporcionaron
    if (items) {
        for (size_t i = 0; i < size; i++) 
        {
            v->data[i] = (copy != NULL && items[i]) ? copy(items[i]) : items[i];
        }
    }

    return v;
}

void vector_destroy(Vector *v) {
    if (!v) return;

    if (v->data && v->free) {
        for (size_t i = 0; i < v->size; i++) 
        {
            if (v->data[i]) 
                v->free(v->data[i]);            
        }
    }

    free(v->data);
    free(v);
}
