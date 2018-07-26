#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "invalid_date.h"
#include "parse_arguments.h"

//Variables globales
short day = -1, month = -1, year = -1, birth_day = -1, birth_month = -1; //-1 para reconocer cuando no se han asignado.
bool signs_vector[12] = {false, false, false, false, false, false, false, false, false, false, false, false};//Los posibles signos invocados.
//IMPORTANTE: este va a ser el orden del vector de acuerdo a los signos:  Aries, Tauro, Géminis, Cáncer, Leo, Virgo, Libra, Escorpión, Sagitario,
//Capricornio, Acuario y Piscis

/*
 * REQUIERE: los argumentos del main.
 * EFECTÚA: recorre todos los argumentos para efectuar distintas funcionalidades:
 * versión 1: comparar cada argumento con --help, y si es igual imprime la ayuda.
 * MODIFICA: n/a
*/
int parse_arguments(int argc, char* argv[])
{
    char array[8];//Para pasar los caracteres a este string, y luego convertir el string a int con atoi.
    int count = 6;//En un posible caso de querer recorrer el anno, ya que no se sabe la cantidad de dígitos del anno, téngase en cuenta de que
                  //un posible anno inicia SIEMPRE en la posición 6.
    short temporal_month;
    //Ciclo donde recorre por todos los argumentos, téngase en cuenta que cada argumento se separa por un espacio.
    for ( int index = 1; index < argc; ++index )
    {
       //En caso de que el usuario solicite ayuda (--help).
        if ( strcmp(argv[index], "--help") == 0 )
        {
            print_help();//Imprimo la ayuda.
            return 1;
        }

        //Se verificará si el primer caracter es un número, esto para tratarlo como una fecha (con o sin año).

        //Evalúo el primer caracter del argumento.
        if( isdigit(argv[index][0]) != 0 )
        {
            //Para guardar las variables, se recorrerá el arreglo asumiendo el formato dd/mm/aaaa.
            //Por lo que se consultará primero si es número, para luego hacer un cast y guardar el número en las variables globales.
            //Para hacer pasar de un char a int, se tiene que hacer un cast al caracter y restarle 48: int numero = (int) ('9') - 48;
            if(  isdigit(argv[index][1]) != 0 && argv[index][2] == '/')//Verifico si el caracter en la posición 1 es número y si lo que sigue es un /.
            {
                //Si entra en el if, es que el formato es el correcto.

                //Pregunto respectivamente si el caracter 3 y 4 son números.
                if( isdigit(argv[index][3]) != 0 && isdigit(argv[index][4]) != 0 )
                {
                    //Si entra hasta acá, es que al menos hay un día y un mes.
                    array[0] = argv[index][3];
                    array[1] = argv[index][4];

                    if( argv[index][5] == '/' )//Pregunta si hay un '/' a ver si digitó o no un anno.
                    {
                        if( day != -1 )//Si ya he guardado datos en las variables
                        {
                            continue;//Regreso al for, no es necesario realizar más acciones.
                        }

                        temporal_month = atoi(array);
                        //Si entra el if, quiere decir que puede que se haya digitado un anno y no se han guaradado datos en las variables para
                        //la fecha. Restauro los valores del array.
                        array[0] = ' ';
                        array[1] = ' ';
                        array[2] = ' ';//Para quitar un posible \0 que se pone en la fecha de nacimiento.

                        while(argv[index][count] != '\0')//Ciclo que recorre el resto del string hasta encontrar el fin.
                        {
                            if( isdigit(argv[index][count]) != 0 )
                            {
                                array[count - 6] = argv[index][count];//-6 para aprovechar el contador que recorre el anno.  Ya que su valor inicial
                                                                 //sería 6 - 6 = 0. Así pongo el el caracter en la posición inicial e iría aumentando.
                            }
                            else//Error de al escribir el anno.
                            {
                                 return fprintf(stderr, "horoscopo: error: anno incorrecto.\n");
                            }

                            if(count == 10)//Si el anno fuera de 4 dígitos o menos, no tendría porqué llegar acá.  Pero es para verificar si ingresó
                                            //un valor más grande.  Téngase en cuenta que el contador inicia en 6, por eso el 10.
                            {
                                return fprintf(stderr, "horoscopo: error: anno sólo puede tener 4 dígitos o menos.\n");
                            }

                            ++count;
                        }

                        if(count == 6)//Error ya que ingresó esto: dd/mm/
                        {
                            return fprintf(stderr, "horoscopo: error: formato de fecha incorrecto.  Utilice este formato: dd/mm[/aaaa]\n");
                        }
                        else
                        {
                            //Si llego hasta acá, es que hay un anno de 4 dígitos o menos, por ende hay una fecha normal.
                            day = atoi(argv[index]);
                            month = temporal_month;
                            year = atoi(array);
                            if( invalid_date(day, month, year) == true )//Fecha inválida
                            {
                                return fprintf(stderr, "horoscopo: error: fecha inválida\n");
                            }
                        }
                        count = 6;//Restauro valor.
                    }
                    else if(argv[index][5] == '\0')//Pregunta si es el final del string, si pasa el if sólo ingresó el día y el mes.
                    {
                        //Si aún no hay datos guardatos en las variables para la fecha de nacimiento.
                        array[2] = '\0';//Para evitar que se cole algún número suelto después de la poscición 1.
                        birth_day = atoi(argv[index]);
                        birth_month = atoi(array);
						
			if( invalid_date(birth_day, birth_month, -1) == true )//Fecha de nacimiento inválida.
			{
			    return fprintf(stderr, "horoscopo: error: fecha de nacimiento inválida\n");
			}
			else
			{
			    translate_birthdate();
			}
                    }
                    else
                    {
                        return fprintf(stderr, "horoscopo: error: formato de fecha incorrecto.  Formato: dd/mm[/aaaa]\n");
                    }
                }
                else//Error de formato.
                {
                    return fprintf(stderr, "horoscopo: error: formato de fecha incorrecto.  Formato: dd/mm[/aaaa]\n");
                }

            }
            else//Error de formato.
            {
                return fprintf(stderr, "horoscopo: error: formato de fecha incorrecto.  Formato: dd/mm[/aaaa]\n");
            }
        }
        else if( isalpha(argv[index][0]) != 0 )//Verifico si el primer caracter es una letra.
        {
            //Note que voy a verificar los signos en minúscula
            //ORDEN:  Aries, Tauro, Géminis, Cáncer, Leo, Virgo, Libra, Escorpión, Sagitario, Capricornio, Acuario y Piscis.
            if( strcmp(argv[index], "aries") == 0 )
            {
                signs_vector[0] = true;
            }
            else if( strcmp(argv[index], "tauro") == 0 )
            {
                signs_vector[1] = true;
            }
            else if( strcmp(argv[index], "geminis") == 0 )
            {
                signs_vector[2] = true;
            }
            else if( strcmp(argv[index], "cancer") == 0 )
            {
                signs_vector[3] = true;
            }
            else if( strcmp(argv[index], "leo") == 0 )
            {
                signs_vector[4] = true;
            }
            else if( strcmp(argv[index], "virgo") == 0 )
            {
                signs_vector[5] = true;
            }
            else if( strcmp(argv[index], "libra") == 0 )
            {
                signs_vector[6] = true;
            }
            else if( strcmp(argv[index], "escorpion") == 0 )
            {
              signs_vector[7] = true;
            }
            else if( strcmp(argv[index], "sagitario") == 0 )
            {
                signs_vector[8] = true;
            }
            else if( strcmp(argv[index], "capricornio") == 0 )
            {
                signs_vector[9] = true;
            }
            else if( strcmp(argv[index], "acuario") == 0 )
            {
                signs_vector[10] = true;
            }
            else if( strcmp(argv[index], "piscis") == 0 )
            {
                signs_vector[11] = true;
            }
            else//No es ningún signo
            {
                return fprintf(stderr, "horoscopo: error: argumento no reconocido, recuerde que los signos tienen que ser en minúscula y sin tildes.\n");
            }
        }
        else
        {
            return fprintf(stderr, "horoscopo: error: argumento no reconocido.\n");
        }
    }
    return 0;
}

/*
 * REQUIERE: una variable help para guardar el string.
 * EFECTÚA: imprime la ayuda para el usuario.
 * MODIFICA: n/a
*/
void print_help()
{
    const char* const help =
            "Ayuda para horoscopo\n\n"
            "El programa se llama en la terminal escribiendo lo siguiente:\n"
            "./horoscopo [fecha] [n signos zodiacales]\n"
            "note que lo que va entre paréntesis cuadrados [] es opcional, horoscopo es obligatorio ponerlo.\n"
            "Para poner la fecha se tiene que seguir este formato: dd/mm[/aaaa], si un día o mes es de un dígito se\n"
            "debe escribir un 0 a la izquierda del número. Así pues un ejemplo sería: 01/14/1997.  Note que el anno es opcional, además de que no importa si el anno\n"
            "tiene 4 dígitos o menos, si tiene más o se ingresa un anno negativo se detiene el programa.\n"
			"Si se ingresa una fecha sin anno, se toma como una fecha de nacimiento y se genera el horoscopo para el signo correspondiente\n"
            "En caso de digitar varias fechas, el programa sólo asumirá la primera de izquierda a derecha.\n"
            "Para digitar los signos debe ser en minúscula y sin tildes: aries, tauro, geminis, cancer, leo, virgo, libra, escorpion, \n"
            "sagitario, capricornio, acuario y piscis.\n"
            "El orden en que se digiten las opciones mencionadas anteriormente no importa.\n"
            "Si se modifica el archivo con las frases, la constancia va a variar.\n"
            "Hay 4 casos posibles de lo que puede suceder de acuerdo a lo que se ponga cuando se llame al programa:\n\n"
            "1) Si no se pone nada: en caso de que no se ponga nada, el programa automáticamente mostrará en la terminal\n"
            "el horóscopo de los 12 signos zodiacales de la fecha actual del sistema.  Note que lo que se imprime hoy, no\n"
            "será lo mismo a lo de otro día, por la ya dicha razón de la fecha.\n\n"
            "2) Si pone la fecha completa: si se digita sólo la fecha, el programa asumirá que quiere el horóscopo de los 12 signos\n"
            "zodiacales de la fecha digitada.\n\n"
            "3) Si digita el/los signo/signos: en caso de que se digite signos, el programa imprimirá en pantalla el horóscopo\n"
            "de los signos puestos de la fecha actual.  Así sea de un sólo signo o de varios.\n\n"
            "4) Si se pone fecha y signo/signos: si se digita las 2 opciones, el programa imprimirá el horóscopo de el/los\n"
            "signo/signos de la fecha digitada.\n\n"
            "5) Si pone fecha sin anno: imprimirá el signo zodiacal respectivo ya que se asume que es una fecha de nacimiento.\n"
            ;
    printf("%s", help);
}

/*
* REQUIERE: las variables globales de la fecha de nacimiento ya con su respectivo valor.
* FECTÚA: convierte la fecha de nacimiento en un número del 0 al 11, para luego asignar true en la posición del número ya traducido.
* MODIFICA: el vector booleano de los signos.
*/
void translate_birthdate()
{
	//Orden de los signos: Aries, Tauro, Géminis, Cáncer, Leo, Virgo, Libra, Escorpión, Sagitario, Capricornio, Acuario y Piscis
	//El signo tendrá un valor mínimo de 0 y máximo de 11, esto por el vector booleano que es de tamanno 12.
	int sign;
	
	//Note que el switch va de acuerdo a los meses, no a los signos, también que ya las fechas están verificadas, por lo que están correctas.
	//Cómo leer el if y el else: if: hasta el día x es el signo y.  else: a partir del día x + 1 (del if) es el signo y + 1.
	switch(birth_month)
	{
		case 1://Enero
		{
			if( birth_day <= 19 )//Capricornio
			{
				sign = 9;
			}
			else//Acuario: 20 de enero o más.
			{
				sign = 10;
			}
			break;
		}
		case 2://Febrero
		{
			if( birth_day <= 18 )//Acuario
			{
				sign = 10;
			}
			else//Piscis
			{
				sign = 11;
			}
			break;
		}
		case 3://Marzo
		{
			if( birth_day <= 20 )//Piscis
			{
				sign = 11;
			}
			else//Aries
			{
				sign = 0;
			}
			break;
		}
		case 4://Abril
		{
			if( birth_day <= 19 )//Aries
			{
				sign = 0;
			}
			else//Tauro
			{
				sign = 1;
			}
			break;
		}
		case 5://Mayo
		{
			if( birth_day <= 20 )//Tauro
			{
				sign = 1;
			}
			else//Géminis
			{
				sign = 2;
			}
			break;
		}
		case 6://Junio
		{
			if( birth_day <= 20 )//Géminis
			{
				sign = 2;
			}
			else//Cáncer
			{
				sign = 3;
			}
			break;
		}
		case 7://Julio
		{
			if( birth_day <= 22 )//Cáncer
			{
				sign = 3;
			}
			else//Leo
			{
				sign = 4;
			}
			break;
		}
		case 8://Agosto
		{
			if( birth_day <= 22 )//Leo
			{
				sign = 4;
			}
			else//Virgo
			{
				sign = 5;
			}
			break;
		}
		case 9://Setiembre
		{
			if( birth_day <= 22 )//Virgo
			{
				sign = 5;
			}
			else//Libra
			{
				sign = 6;
			}
			break;
		}
		case 10://Octubre
		{
			if( birth_day <= 22 )//Libra
			{
				sign = 6;
			}
			else//Escorpio
			{
				sign = 7;
			}
			break;
		}
		case 11://Noviembre
		{
			if( birth_day <= 21 )//Escorpio
			{
				sign = 7;
			}
			else//Sagitario
			{
				sign = 8;
			}
			break;
		}
		case 12://Diciembre
		{
			if( birth_day <= 21 )//Diciembre
			{
				sign = 8;
			}
			else//Capricornio
			{
				sign = 9;
			}
			break;
		}
	}//Fin del switch
	signs_vector[sign] = true;//Al traducir el signo, asigno true en el vector.
}
