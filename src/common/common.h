#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> 
#include <stdbool.h>

/**
 * @brief Lanza un error fatal y termina la ejecución.
 * 
 * Esta función imprime el mensaje de error en stderr y finaliza el programa
 * con código EXIT_FAILURE. Está pensada para situaciones en las que el usuario
 * hace un uso incorrecto de la API de la biblioteca.
 *
 * @param msg Mensaje de error a mostrar.
 */
void raise_error(const char *msg);

/* Callbacks genéricos para manejo de datos */

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
