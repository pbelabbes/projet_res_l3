#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TMAX 500
#define TAILLE_TAB 21

typedef struct InfosTrain InfosTrain;
struct InfosTrain{
	int id;
	char * gareDepart;
	char * gareArrivee;
	char * heureDepart;
	char * heureArrivee;
	float Prix;
	char * reduction;
};

typedef struct liste_train
{
	InfosTrain t;
	struct liste_train *suiv;
} liste_train_t;

typedef liste_train_t* llist;

//ajouter un train en tete de liste 
llist ajouter_train_debut(llist l, InfosTrain info)
{
	liste_train_t* nouveau = malloc(sizeof(liste_train_t));
	
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

	nouveau->suiv=l;

	return nouveau;
}

//ajouter un train en fin de liste
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

void afficher_train(InfosTrain train)
{
	printf("id :%d\n",train.id);
	printf("Gare de depart :%s\n",train.gareDepart);
	printf("Gare d'Arrivee :%s\n",train.gareArrivee);
	printf("Heure de depart :%s\n",train.heureDepart);
	printf("Heure d'arrivee :%s\n",train.heureArrivee);
	printf("Prix :%.2f\n",train.Prix);
	printf("Reduction : %s\n",train.reduction);
}

//retourne le prix après le calcul
float calcul_prix(float p_initial, char * reduc)
{
	float p;

	if(strcmp(reduc,"\n") == 0)
		p=p_initial;
	else if(strcmp(reduc,"REDUC\n") ==0)
			p=p_initial-p_initial*20/100;
		else p=p_initial+p_initial*10/100;

	return p;
}

InfosTrain prix_opti(llist l)
{
	liste_train_t *tmp = l;
	InfosTrain meilleur_prix;
	float best_prix=-1.0, prix_tmp;

	if(tmp != NULL) //s'il existe des trains dans la liste
	{
		meilleur_prix.id=tmp->t.id;

		meilleur_prix.gareDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.gareDepart));
		strcpy(meilleur_prix.gareDepart,tmp->t.gareDepart);

		meilleur_prix.gareArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.gareArrivee));
		strcpy(meilleur_prix.gareArrivee,tmp->t.gareArrivee);

		meilleur_prix.heureDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.heureDepart));
		strcpy(meilleur_prix.heureDepart,tmp->t.heureDepart);

		meilleur_prix.heureArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.heureArrivee));
		strcpy(meilleur_prix.heureArrivee,tmp->t.heureArrivee);
		
		meilleur_prix.Prix=tmp->t.Prix;

		meilleur_prix.reduction = (char *) malloc(sizeof(char) * strlen(tmp->t.reduction));
		strcpy(meilleur_prix.reduction,tmp->t.reduction);

		best_prix = calcul_prix(meilleur_prix.Prix,meilleur_prix.reduction);

		tmp = tmp->suiv;

		while(tmp != NULL)
		{
			prix_tmp = calcul_prix(tmp->t.Prix,tmp->t.reduction);

			if(prix_tmp < best_prix)
			{

				meilleur_prix.id=tmp->t.id;

				meilleur_prix.gareDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.gareDepart));
				strcpy(meilleur_prix.gareDepart,tmp->t.gareDepart);

				meilleur_prix.gareArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.gareArrivee));
				strcpy(meilleur_prix.gareArrivee,tmp->t.gareArrivee);

				meilleur_prix.heureDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.heureDepart));
				strcpy(meilleur_prix.heureDepart,tmp->t.heureDepart);

				meilleur_prix.heureArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.heureArrivee));
				strcpy(meilleur_prix.heureArrivee,tmp->t.heureArrivee);

				meilleur_prix.Prix=tmp->t.Prix;

				meilleur_prix.reduction = (char *) malloc(sizeof(char) * strlen(tmp->t.reduction));
				strcpy(meilleur_prix.reduction,tmp->t.reduction);

				best_prix = prix_tmp;
			}
			tmp = tmp->suiv;
		}
	}
	return meilleur_prix;
}

int main(){
	char *train, *buf;
	llist liste = NULL;

	int i=0, bufsize = TMAX;

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

		while(fgets(train,bufsize , f) != NULL)
			{

			buf = strtok(train, ";");
			tabTrains[i].id = atoi(buf);

			buf = strtok(NULL, ";");
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
			tabTrains[i].Prix = atof(buf);

			buf = strtok(NULL, ";");
			tabTrains[i].reduction = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(tabTrains[i].reduction, buf);

			liste = ajouter_train_fin(liste,tabTrains[i]);
			i++;
		}
		//afficher_liste_train(liste);


		afficher_train(prix_opti(liste));

		for(i=0;i<21;i++){
			//printf("Ligne no : %d\n",i+1);
			//afficher_train(tabTrains[i]);
		}
	}

	
	
	free(train);
	fclose(f);

	return 0;

}



