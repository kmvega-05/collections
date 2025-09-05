#include "vector.h"

// Prototipos de funciones auxiliares
static size_t vector_resolve_index(const Vector *v, int index); 

Vector *vector_make(void **items, size_t size, free_func free, copy_func copy, cmp_func cmp) {
    Vector *v = malloc(sizeof(Vector));
    if (!v) return NULL;

    // Inicializar campos
    v->size = size;
    v->free = free;
    v->copy = copy;
    v->cmp  = cmp;

    // Reservar memoria para el arreglo de datos
    v->data = calloc(size, sizeof(void *));
    if (!v->data) {
        free(v);
        return NULL;
    }

    // Copiar los elementos iniciales si se proporcionan
    if (items) {
        for (size_t i = 0; i < size; i++) 
        {
            v->data[i] = items[i]; 
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

void vector_destroy_at(Vector *v, int index) {
    if (!v) {
        raise_error("vector_destroy_at: vector es NULL");
    }
    size_t idx = vector_resolve_index(v, index);

    if (v->data[idx] && v->free) {
        v->free(v->data[idx]);
    }

    v->data[idx] = NULL;    // Evitar dangling pointer
}

void *vector_get(const Vector *v, int index) {
    if (!v) {
        raise_error("vector_get: vector es NULL");
    }

    size_t idx = vector_resolve_index(v, index);
    if (idx >= v->size) {
        raise_error("vector_get: índice fuera de rango");
    }

    return v->data[idx];
}

void vector_set(Vector *v, int index, void *item) {
    if (!v) { 
        raise_error("vector_set: vector es NULL");
    }
    
    size_t idx = vector_resolve_index(v, index);
    
    if (idx >= v->size) {
        raise_error("vector_set: índice fuera de rango");
    }

    if (v->free && v->data[idx]) {
        v->free(v->data[idx]);
    }

    v->data[idx] = item;
}

// Funciones Auxiliares
// -----------------------------------------------------------------------------------
/**
 * @brief Convierte un índice que puede ser negativo a su equivalente positivo
 *        dentro del rango del vector. Lanza error si está fuera de rango.
 *
 * @param v Puntero al vector.
 * @param index Índice a convertir (puede ser negativo).
 * @return Índice convertido a positivo.
 */
static size_t vector_resolve_index(const Vector *v, int index) {
    if (!v) {
        raise_error("vector_resolve_index: vector is NULL");
    }

    if (index < 0) {
        index = (int)v->size + index;
    }

    if (index < 0 || (size_t)index >= v->size) {
        raise_error("vector_resolve_index: index out of bounds");
    }

    return (size_t)index;
}