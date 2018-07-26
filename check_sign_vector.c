#include <stdbool.h>

#include "check_sign_vector.h"

//Revisa si todo el vector de signos está en false.
bool empty_vector(bool* sign_vector)
{
	for(int sign_counter = 0; sign_counter < 12; ++sign_counter)
	{
		if(sign_vector[sign_counter] == true)
			return false;
	}
	
	return true;
}

//Se ponen todas las posiciones del vector en true para imprimir el horóscopo completo.
void fill_vector(bool* sign_vector)
{
	for(int sign_counter = 0; sign_counter < 12; ++sign_counter)
	{
		sign_vector[sign_counter] = true;
	}
			
}