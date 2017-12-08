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
	float Prix;
	char * reduction;
};

typedef struct liste_train
{
	InfosTrain t;
	struct liste_train *suiv;
} liste_train_t;

typedef liste_train_t* llist;

llist ajouter_train_debut(llist l, InfosTrain info);
llist ajouter_train_fin(llist l, InfosTrain info);
//void afficher_liste_train(llist l);
int duree_int(char h_debut[TMAX], char h_fin[TMAX]);
float calcul_prix(float p_initial, char * reduc);
//void afficher_train(InfosTrain train);
char * cast_train(InfosTrain train);
char* duree_string(int difference);
InfosTrain duree_opti(llist l);
void afficher_train(InfosTrain train);
InfosTrain prix_opti(llist l);
char * train_liste(llist l);
llist creation_liste_InfosTrains(InfosTrain info);
void strtoupper(char *str);
int castHeure(char *hDepart);
llist trancheHoraire(InfosTrain tabTrains[],char *gDepart,char* gArrivee,char* hMin,char* hMax);
char * prepareRequest(char *requete_client);
//llist lire_fichier();
llist element_i(llist liste, int indice);
llist trancheHoraire_list(llist liste,char *gDepart,char* gArrivee,char* hMin,char* hMax);
void triBulles(InfosTrain T[],int TT);
InfosTrain premierTrainDispo(InfosTrain tab[],int TT,int horaire);
llist listeTousLesTrains(InfosTrain tabTrains[],char *gDepart,char* gArrivee);
llist trainSatisfaisant(InfosTrain tabTrains[],char *gDepart, char* gArrivee, char* hDepart);
int castHeure2(char *hDepart);
