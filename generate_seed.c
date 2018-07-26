#include "generate_seed.h"

/*
 * REQUIERE: 4 variables int de la fecha, y el signo.
 * EFECTÚA: hace una serie de operaciones al día, mes y anno para poder reconocer qué es que, esto ya que se generaría una misma semila con las fechas
 * 1/4/97 y 4/1/97, por eso las operaciones. Para terminar de retornar la semilla.
 * MODIFICA: los 3 parámetros para la fecha, y la semilla.
 *
 * Análisis: para mantener constancia, qué tal si mandamos por parámetro lo siguiente: un número que sea único para cada fecha, y  que cada
 * signo tenga un sólo número asignado.  Así pues mando la suma del número de la fecha y del número del signo, así creo que mantendría constancia.
 * Para el número de la fecha puede ser la suma del día, con el mes, con el año; por ejemplo: 01/11/2017: 1 + 11 + 2017.  Y le suma el número
 * asignado para el signo.  Sólo ocupo reconocer si el usuario manda o no signo, por lo que se me ocurre mandar por parámetro una variable booleana,
 * y verificar con un if si mandó con signo o no.
 * Actualizado: hay un error, ya que la fecha 1/9/1997 va a ser lo mismo que 9/1/1997, por lo que para solucionarlo se a solicitar en los parámetros
 * (por separado)el día, el mes y el año, luego lo que se va a hacer es una operación distinta a cada variable.  Así pues (por ejemplo) al día se le
 * sumará 5, el mes se eleva a la 2 y el año se divide entre 8.
*/

int generate_seed(int day, int month, int year, int sign)
{
    int seed;
    day += 5;
    month *= 2;
    year *= 4;
    sign += 3;

    seed = day + month + year + sign;//Cambio de semilla.
    return seed;
}