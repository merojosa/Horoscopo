#include <stdbool.h>

#include "invalid_date.h"

//Debe recibir como parametros las variables globales de day, month y year, devuelve true si la fecha es invalida y false en caso contrario.
//Note que este metodo solo se llamara en caso de que el usuario escriba alguna fecha, si no escribe nada no se llama.
bool invalid_date(short day, short month, short year)
{
	bool invalid = false;
	
	
	if(day == 0)
		return true;
	
	if(day == -1)
		return false;
	
	switch(month)
	{
		
		//Meses con 31 dias
		case 1: 
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(day > 31)
				invalid = true;
			break;
		case 4: 
		case 6:
		case 9:
		case 11:
			if(day > 30)
				invalid = true;
			break;
		//Febrero: bisiesto?
		case 2:
			if( year == -1 )//En caso de que se verifique fecha de nacimiento.
			{
				if( day > 29 )
					invalid = true;
			}
			else if(is_leap_year(year))
			{
				if(day > 29)
					invalid = true;
			}
			else
			{
				if(day > 28)
					invalid = true;
			}
			break;
			
		default: invalid = true;
								
	}
	return invalid;
}

//Devuelve true si year es bisiesto, false si no.
bool is_leap_year(short year)
{
	if(( year % 4 == 0 && year % 100 != 0 ) || ( year % 400 == 0 ))
		return true;
	else
		return false;
}
