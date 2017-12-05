#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// reduc : 0 si pas de reduction, 1 si 20% de reduction, 2 si 10% de supplément
int prix(int p_initial, int reduc)
{
	int p;

	switch (reduc)
	{
		case 0:
			p=p_initial;
			break;			
		case 1:
			p=p_initial-p_initial*20/100;
			break;			
		case 2:
			p=p_initial+p_initial*10/100;
			break;			
	}
	return p;
}

int main ()
{
	printf("prix : %d", prix(50,2));				
	
	return 0;

}
