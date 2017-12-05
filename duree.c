#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TVILLE 100
#define TMAX 100

//retourne la durée sous forme d'un string (pour l'afficher après par ex)
char* duree_string(int difference)
{
	int h3, min3;
	char *temps=malloc(25), tmp[5];
	
	min3 = difference% 60;
	h3 = (difference- min3) / 60;

	snprintf(temps, 5, "%d", h3);
	strcat(temps,"h");
	snprintf(tmp, 5, "%d", min3);
	strcat(temps,tmp);
	strcat(temps,"min"); 
	
	return temps;
	
}

//retourne la durée en minutes sous forme d'un int pour les calculs
int duree_int(char h_debut[TMAX], char h_fin[TMAX])
{
	int h1, h2, min1, min2, temps1, temps2, difference;
		
	h1 = atoi(strtok(h_debut, ":"));
	min1 = atoi(strtok(NULL, ":"));

	h2 = atoi(strtok(h_fin, ":"));
	min2 = atoi(strtok(NULL, ":"));

	temps1= h1 * 60 + min1;
	temps2= h2 * 60 + min2;
	difference= temps2-temps1;
	
	return difference;
}

int main ()
{
	char horaire_dep[] = "15:40", horaire_fin[] = "18:20";	
	int duree = duree_int(horaire_dep, horaire_fin);
	
	printf("duree int : %d \n", duree);
	char * x = duree_string(duree);
	printf("duree string : %s \n ", x);

	return 0;
}


