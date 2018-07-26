#include <stdio.h>

#include "print_signs.h"

//Recibe un numero del 1 al 12 e imprime el encabezado de cada uno de los signos zodiacales segun corresponda
void print_signs(int sign)
{
	switch(sign)
	{
		case 0: printf("Aries (MARZO 20 - ABRIL 19)\n"); break;
		case 1: printf("Tauro (ABRIL 20 - MAYO 20)\n"); break;
		case 2: printf("Geminis (MAYO 21 - JUNIO 20)\n"); break;
		case 3: printf("Cancer (JUNIO 21 - JULIO 22)\n"); break;
		case 4: printf("Leo (JULIO 23 - AGOSTO 22)\n"); break;
		case 5: printf("Virgo (AGOSTO 23 - SEPTIEMBRE 22)\n"); break;
		case 6: printf("Libra (SEPTIEMBRE 23 - OCTUBRE 22)\n"); break;
		case 7: printf("Escorpio (OCTUBRE 23 - NOVIEMBRE 21)\n"); break;
		case 8: printf("Sagitario (NOVIEMBRE 22 - DICIEMBRE 21)\n"); break;
		case 9: printf("Capricornio (DICIEMBRE 22 - ENERO 19)\n"); break;
		case 10: printf("Acuario (ENERO 20 - FEBRERO 18)\n"); break;
		case 11: printf("Piscis (FEBRERO 19 - MARZO 20)\n"); break;	
	}
}