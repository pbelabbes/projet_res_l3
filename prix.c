#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//reduc : 0 si pas de reduction, 1 si 20% de reduction, 2 si 10% de supplément
//retourne le prix après le calcul
float prix(float p_initial, int reduc)
{
	float p;

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
	printf("prix : %.2f", prix(50,0));				
	
	return 0;

}
