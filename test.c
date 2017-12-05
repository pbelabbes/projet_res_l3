#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TMAX 500

typedef struct InfosTrain InfosTrain;
struct InfosTrain{
	char * gareDepart;
	char * gareArrivee;
	char * heureDepart;
	char * heureArrivee;
	float Prix;//PAs oublier De cAster le prix Du trAjet AvAnt De le stocker DAns le tAbleAu
	char * reduction;
};

void trainSatisfaisant(InfosTrain tabTrains[],char *gare){
	int i=0;
	while(tabTrains[i].gareArrivee!=gare){
		printf("%d \n",i);
		i++;
	}

}


int main(){
	char *train = NULL, *gDepart, *gArrivee;
	char *hDepart, *hArrivee;
	size_t bufsize = TMAX;
	char *prix, *reduc;
	int i=0;
	train = (char *)malloc(TMAX);
	InfosTrain tabTrains[21];
	FILE *f = NULL;
	f=fopen("Trains.txt", "r");
	if(f == NULL)
	{
		printf("Erreur ouverture fichier \n");
		exit(0);
	}
	else{
		while(!feof(f)){
		
			getline(&train,&bufsize , f);

			
			gDepart = strtok(train, ";");
			tabTrains[i].gareDepart = gDepart;
			//printf("Gare de depart :%s\n",tabTrains[i].gareDepart);
			
			gArrivee= strtok(NULL, ";");
			tabTrains[i].gareArrivee = gArrivee;
			//printf("Gare d'arrivee%s\n",tabTrains[i].gareArrivee);
			
			hDepart= strtok(NULL, ";");
			tabTrains[i].heureDepart = hDepart;
			//printf("Heure de depart :%s\n",tabTrains[i].heureDepart);

			hArrivee= strtok(NULL, ";");
			tabTrains[i].heureArrivee = hArrivee;
			//printf("Heure d'arrivee :%s\n",tabTrains[i].heureArrivee);

			prix= strtok(NULL, ";");
			tabTrains[i].Prix = atoi(prix);
			//printf("Prix :%.2f\n",tabTrains[i].Prix);
			
			reduc= strtok(NULL, ";");
			tabTrains[i].reduction = reduc;
			//printf("Reduction : %s\n",tabTrains[i].reduction);
			printf("Ligne no : %d\n",i+1);
			i++;
		
		}
		for(i=0;i<21;i++){

			printf("Gare de depart :%s\n",tabTrains[i].gareDepart);
			printf("Gare d'Arrivee :%s\n",tabTrains[i].gareArrivee);
			printf("Heure de depart :%s\n",tabTrains[i].heureDepart);
			printf("Heure d'arrivee :%s\n",tabTrains[i].heureArrivee);
			printf("Prix :%.2f\n",tabTrains[i].Prix);
			printf("Reduction : %s\n",tabTrains[i].reduction);
		
		}
	}
		
	//trainSatisfaisant(tabTrains,"Gare de Lyon");
	
	fclose(f);
	
}



