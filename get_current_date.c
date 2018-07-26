#include <stdlib.h>
#include <time.h>

#include "get_current_date.h"

/*
 * REQUIERE: la biblioteca time.h, un arreglo de int y un arreglo de char.
 * EFECTÚA: guarda en el arreglo de int los valores actuales de la fecha, nótese que el arreglo en el que guardo los valores de la fecha es un string
 * por lo que con la función atoi lo convierto de string a int.  Así en día devolverá de 1 a 30, el mes devolverá de 1 a 12 (de acuerdo al  mes,
 * siendo enero: 1 y diciembre: 12) y el anno.  Para al final devolver la dirección de memoria del arreglo de int, note que este arreglo no se
 * destruye pues es un valor estático
 * MODIFICA: el arreglo de int, el arreglo de char y la estructura local_time.
 *
 * NOTAS: note que el arreglo está en orden d/m/a.  Por lo que si se quiere accceder al mes (por ejemplo) tendría que ser date_array[1],
 * también que estoy devolviendo una dirección de memoria, por lo que tengo que guardar dicha dirección en un puntero, así pues un ejemplo sería:
 * int* ptr = get_current_date();
 * Y para accder a dichos valores:
 * int day = *ptr;
 * int month = *(ptr + 1);
 * int year = *(ptr + 2);
*/
int* get_current_date()
{
    time_t timer = time(0);//Obtener el tiempo actual.
    struct tm *local_time = localtime(&timer);//Estructura utilizada para poder usar en el strftime.
    char date[20];//La cantidad máxima de caracteres para guardar en el arreglo es de 20.
    static int date_array[3];//Arreglo estático para guardar los enteros de día, mes y anno.

    //dia: %d, mes: %m, anno: %Y

    for(int count = 0; count < 4; ++count)//Ciclo para guardar los valores de la fecha en el arreglo de int.
    {
        if(count == 0)
        {
            strftime(date, 20, "%d", local_time);//Obtengo, mediante strftime, el día (%d).
        }
        else if(count == 1)
        {
            strftime(date, 20, "%m", local_time);//mes
        }
        else
        {
            strftime(date, 20, "%Y", local_time);//anno
        }
        date_array[count] = atoi(date);
    }

    return date_array;//Retorno la dirección de memoria, no se pierde ya que es static.
}