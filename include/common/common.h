#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>  // para size_t
#include <stdbool.h>

/**
 * @brief Callback para copiar un elemento.
 * 
 * - Debe devolver un puntero a una nueva copia en heap del elemento.
 */
typedef void *(*copy_func)(const void *elem);

/**
 * @brief Callback para liberar un elemento.
 *
 * - Se utiliza cuando la estructura es dueña del elemento.
 */
typedef void (*free_func)(void *elem);

/**
 * @brief Callback para comparar dos elementos.
 *
 * - Devuelve <0 si a<b, 0 si a==b, >0 si a>b.
 */
typedef int (*cmp_func)(const void *a, const void *b);

#endif // COMMON_H
