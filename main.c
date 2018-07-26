#include "read_file.h"
#include "parse_arguments.h"

int main(int argc, char** argv)
{
	if(parse_arguments(argc,argv) != 0)
	{
		return 1;
	}
	
	read_file(day, month, year, signs_vector);
	return 0;
}
