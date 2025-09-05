#ifndef VECTOR_H
#define VECTOR_H

#include "common/common.h"

/**
 * @brief Vector genérico de tamaño fijo.
 * 
 * Para un mejor funcionamiento de la estructura el usuario puede proporcionar las siguientes funciones:
 *
 * - `void free(void *item)`: Función que libera la memoria reservada por un elemento. Si se proporciona,
 *  el ownership de los datos pasa al vector, si no se proporciona el usuario es el responsable de liberar la memoria de los elementos.   

 * - `void *copy(void *item)`: Función que realiza la copia profunda de un elemento para funciones específicas. Si no se proporciona se realizarán
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
 * @note Los elementos se copian superficialmente(comparten espacio de memoria con los pasados por parámetro)
 * @return Puntero al vector creado, o NULL si ocurre un error de asignación.
 */
Vector *vector_make(void **items, size_t size,
                    free_func free, copy_func copy, cmp_func cmp);

/**
 * @brief Libera un vector y todos sus elementos usando free_func.
 *
 * @param v Puntero al vector a destruir.
 * 
 * @note Si el vector no cuenta con función de liberación simplemente se libera la estructura.
 */
void vector_destroy(Vector *v);

/**
 * @brief Libera el elemento del vector y asigna NULL en la posición especificada.
 *        Se permiten índices negativos para indexar desde el final.
 *
 * @param v Puntero al vector.
 * @param index Índice del elemento a destruir.
 * 
 * @note Si el vector no cuenta con función de liberación solamente se asigna NULL en la posición.
 *
 */
void vector_destroy_at(Vector *v, int index);

/**
 * @brief Obtiene el elemento en un índice del vector (soporta índices negativos).
 *
 * El valor retornado es un `void *`. El usuario debe castear explícitamente
 * al tipo correspondiente (ej: `(Person *)` o `(char *)`).
 *
 * @param v Puntero al vector (no NULL).
 * @param index Índice del elemento.
 * @return Puntero al elemento o NULL en caso de error interno.
 */
void *vector_get(const Vector *v, int index);

/**
 * @brief Reemplaza el elemento en un índice del vector (soporta índices negativos).
 *
 * El parámetro `item` se recibe como `void *`. El usuario debe castear el objeto
 * explícitamente antes de insertar.
 *
 * @param v Puntero al vector (no NULL).
 * @param index Índice donde colocar el nuevo elemento.
 * @param item Nuevo elemento.
 */
void vector_set(Vector *v, int index, void *item);

#endif // VECTOR_H
