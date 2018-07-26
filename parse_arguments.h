#include <stdbool.h>

//Variables globales
extern short day, month, year, birth_day, birth_month;
extern bool signs_vector[12];

//Prototipos
void print_help();
void translate_birthdate();
int parse_arguments(int argc, char* argv[]);
