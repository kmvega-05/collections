#ifndef VECTOR_H
#define VECTOR_H

#include "../common/common.h"

/**
 * @brief Vector genérico de tamaño fijo.
 * 
 * Para un mejor funcionamiento de la estructura el usuario puede proporcionar las siguientes funciones:
 *
 * - `void free(void *item)`: Función que libera la memoria reservada por un elemento. Si se proporciona,
 *  el ownership de los datos pasa al vector, si no se proporciona el usuario es el responsable de liberar la memoria de los elementos.   

 * - `void *copy(void *item)`: Función que realiza la copia profunda de un elemento. Si no se proporciona se realizarán
 *  copias superficiales de los elementos.
 *  
 * - `int cmp(void *a, void *b)`: Función que permite comparar dos elementos. Si no se proporciona, funciones que requieran comparaciones
 *  lanzarán un error en tiempo de ejecución.
 */
typedef struct {
    void    **data;   ///< Arreglo de punteros a elementos
    size_t    size;   ///< Tamaño fijo del vector
    copy_func copy;   ///< Callback para copiar elementos
    free_func free;   ///< Callback para liberar elementos
    cmp_func  cmp;    ///< Callback para comparar elementos
} Vector;

/**
 * @brief Crea un nuevo vector de tamaño fijo.
 *
 * @param items  Array de punteros a elementos iniciales (puede ser NULL).
 * @param size   Tamaño del vector (cantidad de posiciones).
 * @param free   Función para liberar elementos (puede ser NULL).
 * @param copy   Función para copiar elementos (puede ser NULL).
 * @param cmp    Función para comparar elementos (puede ser NULL).
 *
 * @return Puntero al vector creado, o NULL si ocurre un error de asignación.
 */
Vector *vector_make(void **items, size_t size,
                    free_func free, copy_func copy, cmp_func cmp);

/**
 * @brief Libera un vector y todos sus elementos según free_func.
 *
 * @param v Puntero al vector a destruir.
 */
void vector_destroy(Vector *v);



#endif // VECTOR_H
