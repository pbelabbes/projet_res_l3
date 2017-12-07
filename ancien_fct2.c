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


typedef struct liste_train
{
	InfosTrain t;
	struct liste_train *suiv;
} liste_train_t;

typedef liste_train_t* llist;



//FONCTION QUI MET EN MAJ
void strtoupper(char *str)
{
    for ( ; *str ; str++)
        *str = toupper(*str);
}

//fonction qui cast une horaire de train en int
int castHeure(char *hDepart){
//alocation mémoire
	char *tmp=(char*)malloc(5*sizeof(char));
	strcpy(tmp,hDepart);
	char *heure=(char*)malloc(4*sizeof(char)),*minutes=(char*)malloc(2*sizeof(char));
//Suppression des ':' entre les heures et les minutes
	heure=strtok(tmp, ":");
	minutes=strtok(NULL, ":");
//Concaténation des h et minutes pour le cast en int
	strcat(heure,minutes);
//renvoi l'horaire en int
	return atoi(heure);
}

llist ajouter_train_fin(llist l, InfosTrain info)
{
	liste_train_t* nouveau = malloc(sizeof(liste_train_t));
	liste_train_t* tmp = l;

	if(nouveau == NULL)
		exit(EXIT_FAILURE); //allocation a échouée

	nouveau->t.id=info.id;
		
	nouveau->t.gareDepart = (char *) malloc(sizeof(char) * strlen(info.gareDepart));
	strcpy(nouveau->t.gareDepart,info.gareDepart);

	nouveau->t.gareArrivee = (char *) malloc(sizeof(char) * strlen(info.gareArrivee));
	strcpy(nouveau->t.gareArrivee,info.gareArrivee);

	nouveau->t.heureDepart = (char *) malloc(sizeof(char) * strlen(info.heureDepart));
	strcpy(nouveau->t.heureDepart,info.heureDepart);

	nouveau->t.heureArrivee = (char *) malloc(sizeof(char) * strlen(info.heureArrivee));
	strcpy(nouveau->t.heureArrivee,info.heureArrivee);
	
	nouveau->t.Prix=info.Prix;

	nouveau->t.reduction = (char *) malloc(sizeof(char) * strlen(info.reduction));
	strcpy(nouveau->t.reduction,info.reduction);

	nouveau->suiv = NULL;
	if(l == NULL) //si la liste est vide, on renvoie l'élément créé
	{
		return nouveau;
	}
	else 
	{
		while(tmp->suiv != NULL)
		{
			tmp = tmp->suiv;
		}
		tmp->suiv = nouveau;
		return l;
	}
}


//Fonction qui affiche l'heure  la plus proche du prochain train partant de la gare gDepart
llist trancheHoraire(InfosTrain tabTrains[],char *gDepart,char* gArrivee,char* hMin,char* hMax){
	//Variable de taille max à renvoyer à la fin de la fonction
	int horaireD,min,max;
	llist nouveau=NULL;
	//Tableau pour stocker les numéro de trajet
	int tab[TAILLE_TAB],indiceTab=0,i,gare=0;
	
	//Boucle pour stocker les numéros de trajet qui partent de la même gare que l'utilisateur 
	for(gare=0;gare<TAILLE_TAB;gare++){
		if(strcmp(tabTrains[gare].gareDepart,gDepart)==0 && strcmp(tabTrains[gare].gareArrivee,gArrivee)==0) {
		//tab stock des entiers contenant les heures de depart
			tab[indiceTab]=gare;
			//On incrémente de 1 le nombre de valeur correspondante 
			indiceTab++;
		}
	} 
	
	//cast en int de la tranche horaire de l'utilisateur :
	min=castHeure(hMin);
	max=castHeure(hMax);
	
	if(indiceTab>0){
		
		printf("TRAINS DISPO :\n\n");
		//début test tranche horaire par une boucle
		for(i=0;i<indiceTab;i++){
			horaireD=castHeure(tabTrains[tab[i]].heureDepart);
			//test si l'horaire des trains disponible est dans la tranche horaire saisie par l'utilisateur
			//si oui ajoute dans la liste, sinon rien.
			if((horaireD>=min) && (horaireD<=max)){
				nouveau=ajouter_train_fin(nouveau,tabTrains[tab[i]]);
			}
		}
	}
	return nouveau;
}


void afficher_liste_train(llist l)
{
	liste_train_t *tmp = l;
	int i=0;
	while(tmp != NULL)
	{
		printf("Ligne no : %d\n",i+1);

		printf("id :%d\n",tmp->t.id);
		printf("Gare de depart :%s\n",tmp->t.gareDepart);
		printf("Gare d'Arrivee :%s\n",tmp->t.gareArrivee);
		printf("Heure de depart :%s\n",tmp->t.heureDepart);
		printf("Heure d'arrivee :%s\n",tmp->t.heureArrivee);
		printf("Prix :%.2f\n",tmp->t.Prix);
		printf("Reduction : %s\n",tmp->t.reduction);

		tmp = tmp->suiv;
		i++;
	}
}


int main(){
	char *train, *buf;
	llist liste=NULL;
	int i=0, bufsize = TMAX;
	char *trainrecherche=malloc(sizeof(char)*30),*heurerecherche=malloc(sizeof(char)*30),*heurerecherche2=malloc(sizeof(char)*30);
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
			
			//ajout de la ligne dans une liste
			liste = ajouter_train_fin(liste,tabTrains[i]);
			i++;
		}
		//Affichage de tous les trains
		afficher_liste_train(liste);
	}
	//Informations de l'utilisateur
	printf("De quel gare voulez vous partir ? \n");
	scanf("%[^\n]",trainrecherche);
	getchar();//Vider le stdin (le \n reste) avant d'utiliser le fgets
	printf("Où voulez vous partir ? \n");
	
	scanf("%[^\n]",trainrecherche2);
	
	printf("heure min\n");
	scanf("%s",heurerecherche);
	printf("heure max\n");
	scanf("%s",heurerecherche2);
	
	strtoupper(trainrecherche);
	strtoupper(trainrecherche2);
	
	
	free(train);
	
	
	afficher_liste_train(trancheHoraire(tabTrains,trainrecherche,trainrecherche2,heurerecherche,heurerecherche2));
	fclose(f);

	return 0;

}



