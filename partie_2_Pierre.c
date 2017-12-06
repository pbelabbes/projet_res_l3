#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TMAX 500
#define TAILLE_TAB 21

typedef struct InfosTrain InfosTrain;
struct InfosTrain{
	char * gareDepart;
	char * gareArrivee;
	char * heureDepart;
	char * heureArrivee;
	float Prix;//PAs oublier De cAster le prix Du trAjet AvAnt De le stocker DAns le tAbleAu
	char * reduction;
};

int Minimum(int a,int b){
	if(a>b){return a;}
	else{return b;}
}

int rechercheGareD(InfosTrain tabTrains[],char *gDepart){
	int gare=-1;
	do{
		gare++;
	}while(strcmp(tabTrains[gare].gareDepart,gDepart)!=0 && gare<20 );
	if (strcmp(tabTrains[gare].gareDepart,gDepart)!=0){
		return -1;//Gare non trouvée
	}
	else{
		return gare;//Gare trouvée
	}

}

int rechercheHeure(InfosTrain tabTrains[],char *hDepart){
//alocation mémoire
	char *heure=malloc(sizeof(char)*4),*minutes=malloc(sizeof(char)*2),*heureCompare=malloc(sizeof(char)*4);
	int min,hactuel;
//Suppression des ':' entre les heures et les minutes
	heure=strtok(hDepart, ":");
	minutes=strtok(NULL, ":");
//Concaténation des h et minutes pour le cast en int
	strcat(heure,minutes);
//cast en int
	atoi(heure);
	
	return 0;
}

//Ce soir jvais passser voir Jules pour qu'il me donne des cours Tinder mdr





/*char* trainSatisfaisant(InfosTrain tabTrains[],char *gDepart,char* hDepart){
	
	char *heure=malloc(sizeof(char)*2),*minutes=malloc(sizeof(char)*2);
	heure=strtok(hDepart, ":");
	minutes=strtok(NULL, ":");
	concat(heure,minutes);
	
	do{
			heure++;
		}while(strcmp(tabTrains[heure].heureDepart,hDepart)!=0 && heure<20 );
		if(strcmp(tabTrains[heure].heureDepart,hDepart)==0){
			return "Trajet trouvé \n";		
		}
		else{ return "COUCOU CEST MOI MDR\n";}
	
}*/

int main(){
	char *train, *buf;
	
	int i=0, bufsize = TMAX;
	char *trainrecherche=malloc(sizeof(char)*30),*heurerecherche=malloc(sizeof(char)*30);
	train = (char *)malloc(TMAX);
	InfosTrain tabTrains[21];
	FILE *f = fopen("Trains.txt", "r");

	if(f == NULL)
	{
		printf("Erreur ouverture fichier \n");
		free(train);
		exit(0);
	}
	else{
		//while(!feof(f)){

			while(fgets(train,bufsize , f) != NULL)
			{
			buf = strtok(train, ";");
			tabTrains[i].gareDepart = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].gareDepart, buf);

			buf = strtok(NULL, ";");
			tabTrains[i].gareArrivee = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].gareArrivee, buf);

			buf = strtok(NULL, ";");
			tabTrains[i].heureDepart = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].heureDepart, buf);

			buf = strtok(NULL, ";");
			tabTrains[i].heureArrivee = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].heureArrivee, buf);

			buf = strtok(NULL, ";");
			tabTrains[i].Prix = atoi(buf);

			buf = strtok(NULL, ";");
			tabTrains[i].reduction = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].reduction, buf);

			i++;
		}

		for(i=0;i<21;i++){
			printf("Ligne no : %d\n",i+1);

			printf("Gare de depart :%s\n",tabTrains[i].gareDepart);
			printf("Gare d'Arrivee :%s\n",tabTrains[i].gareArrivee);
			printf("Heure de depart :%s\n",tabTrains[i].heureDepart);
			printf("Heure d'arrivee :%s\n",tabTrains[i].heureArrivee);
			printf("Prix :%.2f\n",tabTrains[i].Prix);
			printf("Reduction : %s\n",tabTrains[i].reduction);

		}
	}

	printf("De quel gare voulez vous partir ? \n");
	scanf("%s",trainrecherche);
	printf("A quel heure voulez vous partir ? (de format hh:mm)\n");
	scanf("%s",heurerecherche);
	
	
	free(train);
	printf("Trajet no%d\n",rechercheGareD(tabTrains,trainrecherche));
	rechercheHeure(tabTrains,heurerecherche);
	fclose(f);

	return 0;

}



