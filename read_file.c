#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "read_file.h"
#include "get_current_date.h"
#include "generate_seed.h"
#include "lucky_number.h"
#include "print_signs.h"
#include "check_sign_vector.h"

#define PHRASE_LIMIT 1024
#define PHRASE_LENGHT 1024

void read_file(short day, short month, short year, bool* signs_vector)
{	
	char phrases[PHRASE_LIMIT][PHRASE_LENGHT];
	int index = 0; //Cuenta las frases.
	int topic_counter = 1; 
	int seed = 0;
	
	if(empty_vector(signs_vector))
		fill_vector(signs_vector);
	
	//Se realiza el ciclo 12 veces, una para cada signo zodiacal.
	for(int sign_counter = 0; sign_counter <= 11; sign_counter++)
	{
		if(signs_vector[sign_counter] == true)
		{
			printf("\n");
			print_signs(sign_counter);
			if(day == -1)
				seed = get_seed(sign_counter); //Genera una semilla recibiendo como parametro un entero dependiendo del signo zodiacal.
			else
				seed = generate_seed(day, month, year, sign_counter);

			FILE* text_file = fopen("horoscopo.txt", "r");
			if ( text_file == NULL )
			{
				fprintf(stderr, "horoscopo: error: could not open file: horoscopo.txt\n");
			}else
			{
				fgets(phrases[0], PHRASE_LIMIT, text_file);

				while(fgets(phrases[index], PHRASE_LIMIT, text_file) != NULL)
				{
					if(phrases[index][0] == ':')
					{
						++topic_counter;

						if(topic_counter > 1)
						{
							//Genera numero al azar e imprime la frase
							srand(seed);
							int random = (rand() % (index-2))+1;
							printf("%s", phrases[random]);
							//Vuelve el index a 0 para que no se repitan las frases ya elegidas y leer las frases de los nuevos temas.
							index = 0;
						}

					}else
					{
						++index;
					}


				}

				//Se genera un numero y una frase al azar para el ultimo tema.
				int lucky_number = generate_lucky_number(seed);
				int random = rand() % index;
				printf("%s", phrases[random]);
				if(random == 16)
					printf("\n");
				printf("Tu número de la suerte es: %02d\n\n", lucky_number);
				topic_counter = 1;
				index = 0;
			}

		}
	}
	
}

int get_seed(int sign)
{
	int* date_array = get_current_date();
	int day = *date_array;
	int month = *(date_array+1);
	int year = *(date_array+2);
	
	int seed = generate_seed(day, month, year, sign);
	
	return seed;
}
