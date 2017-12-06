#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TMAX 500
#define TAILLE_TAB 21

typedef struct InfosTrain InfosTrain;
struct InfosTrain{
	int id;
	char * gareDepart;
	char * gareArrivee;
	char * heureDepart;
	char * heureArrivee;
	float Prix;//PAs oublier De cAster le prix Du trAjet AvAnt De le stocker DAns le tAbleAu
	char * reduction;
};



//Fonction qui retourne le minimum
int Minimum(int a,int b){
	if(a>b){return a;}
	else{return b;}
}

//FONCTION QUI MET EN MAJ
void strtoupper(char *str)
{
    for ( ; *str ; str++)
        *str = toupper(*str);
}

//fonction qui cast une horaire de train en int
int castHeure(char *hDepart){
//alocation mémoire
	char *heure=malloc(sizeof(char)*4),*minutes=malloc(sizeof(char)*2);
//Suppression des ':' entre les heures et les minutes
	heure=strtok(hDepart, ":");
	minutes=strtok(NULL, ":");
//Concaténation des h et minutes pour le cast en int
	strcat(heure,minutes);
//renvoi l'horaire en int
	return atoi(heure);
}

//Ce soir jvais passer voir Jules pour qu'il me donne des cours Tinder mdr


//Tri de tableau
void triBulles(int T[],int TT){
  int i,j;
  for(i=0;i<TT-2;i++){
    for(j=TT-1;j>=i+1;j--){
	 	if(T[j]<T[j-1]);
  	 }
  }
}

//Fonction qui retourne le prochain train dispo en fonction de l'horaire
int premierTrainDispo(int tab[],int TT,int horaire){
	int i;
	for(i=0;i<TT;i++){
		if(tab[i]>=horaire){
			return tab[i];
		}
	}
	return 0;
}


//Fonction qui affiche l'heure  la plus proche du prochain train partant de la gare gDepart
void trainSatisfaisant(InfosTrain tabTrains[],char *gDepart,char* hDepart,char* gArrivee){
	
	int tab[TAILLE_TAB],indiceTab=0,i,gare=0;//Tableau pour stocker les numéro de trajet
	//Boucle pour stocker les numéros de trajet qui partent de la même gare que l'utilisateur 
	for(i=0;i<TAILLE_TAB;i++){
		if(strcmp(tabTrains[gare].gareDepart,gDepart)==0 && strcmp(tabTrains[gare].gareArrivee,gArrivee)==0) {
			tab[indiceTab]=castHeure(tabTrains[gare].heureDepart);
			indiceTab++;
			gare++;
		}
		else{
			gare++;
		}
	}
	//Vérification si il y a un train partant de la gare recherchée
	if(indiceTab>0){
		//tri du tableau
		triBulles(tab,indiceTab);
	}
	printf("Le premier train disponible est à %d \n",premierTrainDispo(tab,indiceTab,castHeure(hDepart)));
}

int main(){
	char *train, *buf;
	
	int i=0, bufsize = TMAX;
	char *trainrecherche=malloc(sizeof(char)*30),*heurerecherche=malloc(sizeof(char)*30);
	char *trainrecherche2=malloc(sizeof(char)*30);
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
			tabTrains[i].id = atoi(buf);


			buf = strtok(NULL, ";");
			tabTrains[i].gareDepart = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].gareDepart, buf);
			strtoupper(tabTrains[i].gareDepart);
			
			buf = strtok(NULL, ";");
			tabTrains[i].gareArrivee = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].gareArrivee, buf);
			strtoupper(tabTrains[i].gareArrivee);
			
			buf = strtok(NULL, ";");
			tabTrains[i].heureDepart = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].heureDepart, buf);

			buf = strtok(NULL, ";");
			tabTrains[i].heureArrivee = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].heureArrivee, buf);

			buf = strtok(NULL, ";");
			tabTrains[i].Prix = atof(buf);

			buf = strtok(NULL, ";");
			tabTrains[i].reduction = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].reduction, buf);

			i++;
		}
		//Affichage de tous les trains
		for(i=0;i<21;i++){
			printf("Ligne no : %d\n",tabTrains[i].id);

			printf("Gare de depart :%s\n",tabTrains[i].gareDepart);
			printf("Gare d'Arrivee :%s\n",tabTrains[i].gareArrivee);
			printf("Heure de depart :%s\n",tabTrains[i].heureDepart);
			printf("Heure d'arrivee :%s\n",tabTrains[i].heureArrivee);
			printf("Prix :%.2f\n",tabTrains[i].Prix);
			printf("Reduction : %s\n",tabTrains[i].reduction);

		}
	}
	
	//Informations de l'utilisateur
	printf("De quel gare voulez vous partir ? \n");
	scanf("%[^\n]",trainrecherche);
	getchar();//Vider le stdin (le \n reste) avant d'utiliser le fgets
	printf("Où voulez vous partir ? \n");
	
	scanf("%[^\n]",trainrecherche2);
	
	printf("A quel heure voulez vous partir ? (de format hh:mm)\n");
	scanf("%s",heurerecherche);
	printf("La gare d'arrivée est : %s \n",trainrecherche2);
	strtoupper(trainrecherche);
	strtoupper(trainrecherche2);
	
	
	free(train);
	trainSatisfaisant(tabTrains,trainrecherche,heurerecherche,trainrecherche2);
	fclose(f);

	return 0;

}



