#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TMAX 100

typedef struct{
	char* gareDepart;
	char* gareArrivee;
	char* heureDepart;
	char* heureArrivee;
	float Prix;//PAs oublier De cAster le prix Du trAjet AvAnt De le stocker DAns le tAbleAu
}InfosTrain;




int main(){
	char *train = NULL, *gDepart, *gArrivee;
	char *hDepart, *hArrivee;
	size_t bufsize = TMAX;

	train = (char *)malloc(TMAX);
	InfosTrain* tabTrains[30];
	*tabTrains=malloc(sizeof(InfosTrain));
	FILE *f = NULL;
	f=fopen("Trains.txt", "r");
	if(f == NULL)
	{
		printf("Erreur ouverture fichier \n");
		exit(0);
	}
	else{
		while(!feof(f)){
		int i=0;
		getline(&train,&bufsize , f);
		gDepart = strtok(train, ";");
		tabTrains[i].gareDepart = gDepart;
	
		gArrivee= strtok(NULL, ";");
		tabTrains[i].gareArrivee = gArrivee;

		hDepart= strtok(NULL, ";");
		tabTrains[i].heureDepart = hDepart;

		hArrivee= strtok(NULL, ";");
		tabTrains[i].heureArrivee = hArrivee;
		i++;
		}
	}
	int x;
	for(x=0;x<=30;x++){
		printf("%s \n",&tabTrains[x]->gareDepart);
	}
	
	fclose(f);
	
}



