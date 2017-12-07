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


//Tri de tableau
void triBulles(InfosTrain T[],int TT){
  //variablesp our parcourir le tableau
  int i,j;
  //variables pour stocker les valeurs du tab
  char* compare1,*compare2;
  //Structure temporaire pour échanger les valeurs
  InfosTrain tmp;
  
  for(i=0;i<TT-2;i++){
    for(j=TT-1;j>=i+1;j--){
    //allocation mémoire
    	compare1=malloc(sizeof(T[j].heureDepart));
    	compare2=malloc(sizeof(T[j-1].heureDepart));
    //copie des heures de Départ
    	strcpy(compare1,T[j].heureDepart);
    	strcpy(compare2,T[j-1].heureDepart);
    	
    	//Vérification si l'heure est plus petit ou non
	 	if(castHeure(compare1)<castHeure(compare2)) {
	 			//Si la condition est respectée alors on effectue le changement avec notre structure temporaire
	 			tmp.gareDepart=(char *) malloc(sizeof(T[j-1].gareDepart));
				tmp.gareArrivee=(char *) malloc(sizeof(T[j-1].gareArrivee));
				tmp.heureDepart=(char *) malloc(sizeof(T[j-1].heureDepart));
				tmp.heureArrivee=(char *) malloc(sizeof(T[j-1].heureArrivee));
				tmp.reduction=(char *) malloc(sizeof(T[j-1].reduction));
	
				tmp.id=T[j-1].id;
				tmp.gareDepart=T[j-1].gareDepart;
				tmp.gareArrivee=T[j-1].gareArrivee;
				tmp.heureDepart=T[j-1].heureDepart;
				tmp.heureArrivee=T[j-1].heureArrivee;
				tmp.Prix=T[j-1].Prix;
				tmp.reduction=T[j-1].reduction;
	
				T[j-1].id=T[j].id;
				T[j-1].gareDepart=T[j].gareDepart;
				T[j-1].gareArrivee=T[j].gareArrivee;
				T[j-1].heureDepart=T[j].heureDepart;
				T[j-1].heureArrivee=T[j].heureArrivee;
				T[j-1].Prix=T[j].Prix;
				T[j-1].reduction=T[j].reduction;
		
				T[j].id=tmp.id;
				T[j].gareDepart=tmp.gareDepart;
				T[j].gareArrivee=tmp.gareArrivee;
				T[j].heureDepart=tmp.heureDepart;
				T[j].heureArrivee=tmp.heureArrivee;
				T[j].Prix=tmp.Prix;
				T[j].reduction=tmp.reduction;
	 	}
  	 }
  }
}

//Fonction qui retourne le prochain train dispo en fonction de l'horaire
InfosTrain premierTrainDispo(InfosTrain tab[],int TT,int horaire){
	int i;
	//variable temporaire pour manipuler les données sans danger
	char* tmp;
	for(i=0;i<TT;i++){
		//Allocation mémoire
		tmp=malloc(sizeof(tab[i].heureDepart));
		//copie de l'heure de départ dans une variable temporaire pour ne pas changer la valeur
		strcpy(tmp,tab[i].heureDepart);
		//Vérification si les prochaines horaires du tableau sont plus tard que celle passée par l'utilisateur
		if(castHeure(tmp)>=horaire){
			return tab[i];
		}
	}
	//Sinon on renvoi le train du lendemain
	printf("Prochain train demain : \n");
	return tab[0];
}

//Fonction 3 aui affiche tous les trains partant de tel gare et allant à tel gare
llist listeTousLesTrains(InfosTrain tabTrains[],char *gDepart,char* gArrivee){
	//Liste à renvoyer
	llist listeARetourner=NULL;
	int indiceTab=0,i;
	//Tableau pour stocker les numéro de trajet
	InfosTrain tab[TAILLE_TAB];
	//Boucle pour stocker les trains partant et arrivant aux même gares que celles saisie par l'utilisateur 
	for(i=0;i<TAILLE_TAB;i++){
		if(strcmp(tabTrains[i].gareDepart,gDepart)==0 && strcmp(tabTrains[i].gareArrivee,gArrivee)==0) {
			tab[indiceTab]=tabTrains[i];
			//On incrémente de 1 le nombre de trajet vérifiant la condition
			indiceTab++;
		}
	}
	
	//Ajout des trains dans la liste à renvoyer
	for(i=0;i<indiceTab;i++){
		listeARetourner=ajouter_train_fin(listeARetourner,tab[i]);
	}
	//Cas d'erreur si jamais il n'y pas de trains à afficher
	if(indiceTab==0){
		printf("Aucune ligne effectue le trajet %s - %s. \n",gDepart,gArrivee);
		return listeARetourner;	
	}
	//Sinon on retourne la liste sans erreur
	return listeARetourner;
}



//Fonction qui affiche l'heure  la plus proche du prochain train partant de la gare gDepart
llist trainSatisfaisant(InfosTrain tabTrains[],char *gDepart,char* hDepart,char* gArrivee){
	llist listeARetourner=NULL;
	int indiceTab=0,i;//Tableau pour stocker les numéro de trajet
	InfosTrain tab[TAILLE_TAB];
	//Boucle pour stocker les numéros de trajet qui partent de la même gare que l'utilisateur 
	for(i=0;i<TAILLE_TAB;i++){
		if(strcmp(tabTrains[i].gareDepart,gDepart)==0 && strcmp(tabTrains[i].gareArrivee,gArrivee)==0) {
			tab[indiceTab]=tabTrains[i];
			indiceTab++;
		}
	}
	//Verification qu'il y a des trains qui font le trajet
	if(indiceTab>0){
	//Tri des trains disponibles en fonction de l'heure de départ
		triBulles(tab,indiceTab);
		//ajout du prochain train disponible à notre liste à renvoyer
		listeARetourner=ajouter_train_fin(listeARetourner,premierTrainDispo(tab,indiceTab,castHeure(hDepart)));
		return listeARetourner;
	}else{
		//Cas d'erreur : Erreur sur les saisies de gare -- Pas de trajet existant.
		printf("Aucune ligne effectue le trajet %s - %s. \n",gDepart,gArrivee);
		return listeARetourner;
	}
}


int main(){
	char *train, *buf;
	llist liste=NULL;
	llist liste2=NULL;
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
			
			//ajout de la ligne dans une liste
			liste = ajouter_train_fin(liste,tabTrains[i]);
			i++;
		}
		}
		//Affichage de tous les trains
		//afficher_liste_train(liste);
	
	//Informations de l'utilisateur
	printf("De quel gare voulez vous partir ? \n");
	scanf("%[^\n]",trainrecherche);
	getchar();//Vider le stdin (le \n reste) avant d'utiliser le fgets
	printf("Où voulez vous partir ? \n");
	scanf("%[^\n]",trainrecherche2);
	printf("A quel heure voulez vous partir ? (de format hh:mm)\n");
	
	scanf("%s",heurerecherche);
	strtoupper(trainrecherche);
	strtoupper(trainrecherche2);
	
	
	free(train);
	liste=trainSatisfaisant(tabTrains,trainrecherche,heurerecherche,trainrecherche2);
	afficher_liste_train(liste);
	
	
	getchar();
	printf("De quel gare voulez vous partir ? \n");
	scanf("%[^\n]",trainrecherche);
	getchar();//Vider le stdin (le \n reste) avant d'utiliser le fgets
	printf("Où voulez vous partir ? \n");
	scanf("%[^\n]",trainrecherche2);
	
	strtoupper(trainrecherche);
	strtoupper(trainrecherche2);
	liste2=listeTousLesTrains(tabTrains,trainrecherche,trainrecherche2);
	afficher_liste_train(liste2);
	fclose(f);

	return 0;

}



