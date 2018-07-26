#include <stdlib.h>

#include "lucky_number.h"
/*
 * REQUIERE: un parámetro int semilla.
 * EFECTÚA: genera un número aleatorio, a partir de la semilla, entre 0 y 99 para luego retornarla.
 * MODIFICA: la variable random y la semilla.
 */
int generate_lucky_number(int seed)
{
    srand(seed);//Cambio de semilla
    int random = rand() % 100;//0-99
    return random;
}