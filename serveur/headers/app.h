#ifndef APP_H
#define APP_H

#include <ctype.h>
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
void strtoupper(char *str);

//Tri de tableau si les trains ne sont pas triés par horaire
void triBulles(InfosTrain T[],int TT);

//Fonction qui retourne le prochain train dispo en fonction de l'horaire
InfosTrain premierTrainDispo(InfosTrain tab[],int TT,int horaire);

//Fonction 3 aui affiche tous les trains partant de tel gare et allant à tel gare
llist listeTousLesTrains(InfosTrain tabTrains[],char *gDepart,char* gArrivee);

//Fonction 1 qui affiche l'heure  la plus proche du prochain train partant de la gare gDepart
llist trainSatisfaisant(InfosTrain tabTrains[],char *gDepart, char* gArrivee, char* hDepart);

//fonction qui cast une horaire de train en int
int castHeure(char *hDepart);


//recherche du ieme elt dans la liste
llist element_i(llist liste, int indice);


//fct avec une liste 2
llist trancheHoraire_list(llist liste,char *gDepart,char* gArrivee,char* hMin,char* hMax);


//ajouter un train en tete de liste 
llist ajouter_train_debut(llist l, InfosTrain info);


//ajouter un train en fin de liste
llist ajouter_train_fin(llist l, InfosTrain info);



//retourne la durée en minutes sous forme d'un int pour les calculs
int duree_int(char h_debut[TMAX], char h_fin[TMAX]);


//retourne le prix après réduction/supplément
float calcul_prix(float p_initial, char * reduc);


// renvoie un string avec toute les infos du train
char * cast_train(InfosTrain train);


//renvoie un char* à partir d'une liste de train
char * train_liste(llist l);



//retourne la durée sous forme d'un string (pour l'afficher après par ex)
char* duree_string(int difference);


//creer liste à 1 element à partir d'un InfosTrain
llist creation_liste_InfosTrains(InfosTrain info);


//retourne le train avec la durée la plus faible
InfosTrain duree_opti(llist l);


InfosTrain prix_opti(llist l);


char * traiterRequete(char *requete_client);

#endif