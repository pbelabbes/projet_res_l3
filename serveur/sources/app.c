#include "serveur.h"
#include "app.h"

//lis le fichier train.txt et renvoie une liste contenant tout les trains du fichier
/*llist lire_fichier()
{
	char *train, *buf;
	llist liste = NULL;
	int bufsize = TMAX;
	InfosTrain train_unique;
	train = (char *)malloc(TMAX);
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
			train_unique.id = atoi(buf);
			buf = strtok(NULL, ";");
			train_unique.gareDepart = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(train_unique.gareDepart, buf);
			strtoupper(train_unique.gareDepart);
			
			buf = strtok(NULL, ";");
			train_unique.gareArrivee = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(train_unique.gareArrivee, buf);
			strtoupper(train_unique.gareArrivee);
			
			buf = strtok(NULL, ";");
			train_unique.heureDepart = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(train_unique.heureDepart, buf);
			buf = strtok(NULL, ";");
			train_unique.heureArrivee = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(train_unique.heureArrivee, buf);
			buf = strtok(NULL, ";");
			train_unique.Prix = atof(buf);
			buf = strtok(NULL, ";");
			train_unique.reduction = (char *) malloc(sizeof(char) * strlen(buf));
			strcpy(train_unique.reduction, buf);
			
			//ajout de la ligne dans une liste
			liste = ajouter_train_fin(liste,train_unique);
			}
		}
	free(train);
	fclose(f);
	return liste;
}
*/
//FONCTION QUI MET EN MAJ
void strtoupper(char *str)
{
    for ( ; *str ; str++)
        *str = toupper(*str);
}

/*
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
}*/


//Tri de tableau si les trains ne sont pas triés par horaire
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

//Fonction 1 qui affiche l'heure  la plus proche du prochain train partant de la gare gDepart
llist trainSatisfaisant(InfosTrain tabTrains[],char *gDepart, char* gArrivee, char* hDepart){
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

//fonction qui cast une horaire de train en int
int castHeure(char *hDepart)
{
	char *tmp=(char*)malloc(5*sizeof(char));
	char *heure=(char*)malloc(4*sizeof(char)),*minutes=(char*)malloc(2*sizeof(char));
	strcpy(tmp,hDepart);
	heure=strtok(tmp, ":"); //Suppression des ':' entre les heures et les minutes
	minutes=strtok(NULL, ":");

	strcat(heure,minutes); //Concaténation des h et minutes pour le cast en int

	return atoi(heure);
}

//recherche du ieme elt dans la liste
llist element_i(llist liste, int indice)
{
    int i;
    /* On se déplace de i cases, tant que c'est possible */
    for(i=0; i<indice && liste != NULL; i++)
    {
        liste = liste->suiv;
    }
 
    /* Si l'élément est NULL, c'est que la liste contient moins de i éléments */
    if(liste == NULL)
    {
        return NULL;
    }
    else
    {
        /* Sinon on renvoie l'adresse de l'élément i */
        return liste;
    }
}

/*
//Fonction qui affiche l'heure  la plus proche du prochain train partant de la gare gDepart
llist trancheHoraire(InfosTrain tabTrains[],char *gDepart,char* gArrivee,char* hMin,char* hMax)
{	//Variable de taille max à renvoyer à la fin de la fonction
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
*/
//fct avec une liste 2
llist trancheHoraire_list(llist liste,char *gDepart,char* gArrivee,char* hMin,char* hMax)
{	//Variable de taille max à renvoyer à la fin de la fonction
	int horaireD,min,max;
	llist nouveau=NULL;
	liste_train_t *tmp = liste;
	InfosTrain info;
	//Tableau pour stocker les numéro de trajet
	int tab[TMAX],indiceTab=0,i,gare=0;

	//Boucle pour stocker les numéros de trajet qui partent de la même gare que l'utilisateur 
	while(tmp != NULL)
	{
		if(strcmp(tmp->t.gareDepart,gDepart)==0 && strcmp(tmp->t.gareArrivee,gArrivee)==0) {
		//tab stock des entiers contenant les heures de depart
			tab[indiceTab]=gare;
			//On incrémente de 1 le nombre de valeur correspondante 
			indiceTab++;
		}

		tmp = tmp->suiv;

		gare ++;
	} 

	min=castHeure(hMin);
	max=castHeure(hMax);

	if(indiceTab>0){

		//début test tranche horaire par une boucle
		for(i=0;i<indiceTab;i++)
		{
			info = element_i(liste, tab[i])->t;
			horaireD=castHeure(info.heureDepart);
			//test si l'horaire des trains disponible est dans la tranche horaire saisie par l'utilisateur
			//si oui ajoute dans la liste, sinon rien.

			if((horaireD>=min) && (horaireD<=max)){
				nouveau=ajouter_train_fin(nouveau,info);
			}

		}
	}
	return nouveau;
}

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

/* plus besoin car printf(%s) de cast train
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
*/

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

//retourne le prix après réduction/supplément
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

// renvoie un string avec toute les infos du train
char * cast_train(InfosTrain train)
{
	char * train_cat = (char *)malloc(100*sizeof(InfosTrain));
	char *tmp = (char *)malloc(sizeof(InfosTrain));

	strcpy(train_cat,"\nTrain Numéro     : ");
	snprintf(tmp, 6, "%d", train.id);
	strcat(train_cat,tmp);
	strcat(train_cat,"\nGare de départ   : ");
	strcat(train_cat,train.gareDepart);
	strcat(train_cat,"\nGare d'Arrivee   : ");
	strcat(train_cat,train.gareArrivee);
	strcat(train_cat,"\nHeure de depart  : ");
	strcat(train_cat,train.heureDepart);
	strcat(train_cat,"\nHeure d'arrivee  : ");	
	strcat(train_cat,train.heureArrivee);
	strcat(train_cat,"\nDurée de trajet  : ");
	strcat(train_cat,duree_string(duree_int(train.heureDepart,train.heureArrivee)));
	strcat(train_cat,"\nPrix \t\t : ");
	snprintf(tmp, 6, "%.2f", calcul_prix(train.Prix, train.reduction));
	strcat(train_cat, tmp);
	strcat(train_cat,"\n\n---------------------------\n ");

	return train_cat;
}

//renvoie un char* à partir d'une liste de train
char * train_liste(llist l)
{
	liste_train_t *tmp = l;
	char * liste_train_cat = (char *)malloc(100*sizeof(InfosTrain));

	while(tmp != NULL)
	{
		strcat(liste_train_cat, cast_train(tmp->t));
		tmp=tmp->suiv;
	}
	return liste_train_cat;
}

// inutile
/*
void afficher_liste_train(llist l)
{
	liste_train_t *tmp = l;
	int i=0;
	while(tmp != NULL)
	{
		printf("Ligne no \t : %d\n",i+1);
		printf("%s \n",cast_train(tmp->t));
		tmp = tmp->suiv;
		i++;
	}
}
*/

/*
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
*/

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

//creer liste à 1 element à partir d'un InfosTrain
llist creation_liste_InfosTrains(InfosTrain info)
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
	nouveau->suiv=NULL;

	return nouveau;
}

//retourne le train avec la durée la plus faible
InfosTrain duree_opti(llist l)
{
	liste_train_t *tmp = l;
	InfosTrain meilleur_duree;
	int best_duree=-1, duree_tmp;
	char *tmph1, *tmph2;

	if(tmp != NULL) //s'il existe des trains dans la liste
	{
		meilleur_duree.id=tmp->t.id;
		meilleur_duree.gareDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.gareDepart));
		strcpy(meilleur_duree.gareDepart,tmp->t.gareDepart);
		meilleur_duree.gareArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.gareArrivee));
		strcpy(meilleur_duree.gareArrivee,tmp->t.gareArrivee);
		meilleur_duree.heureDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.heureDepart));
		strcpy(meilleur_duree.heureDepart,tmp->t.heureDepart);
		meilleur_duree.heureArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.heureArrivee));
		strcpy(meilleur_duree.heureArrivee,tmp->t.heureArrivee);
		meilleur_duree.Prix=tmp->t.Prix;
		meilleur_duree.reduction = (char *) malloc(sizeof(char) * strlen(tmp->t.reduction));
		strcpy(meilleur_duree.reduction,tmp->t.reduction);
		tmph1 = (char *) malloc(sizeof(char) * strlen(tmp->t.heureDepart));
		strcpy(tmph1,meilleur_duree.heureDepart);
		tmph2 = (char *) malloc(sizeof(char) * strlen(tmp->t.heureArrivee));
		strcpy(tmph2,meilleur_duree.heureArrivee);
		best_duree = duree_int(tmph1,tmph2);
		tmp = tmp->suiv;

		while(tmp != NULL)
		{
			tmph1 = (char *) malloc(sizeof(char) * strlen(tmp->t.heureDepart));
			strcpy(tmph1,tmp->t.heureDepart);
			tmph2 = (char *) malloc(sizeof(char) * strlen(tmp->t.heureArrivee));
			strcpy(tmph2,tmp->t.heureArrivee);
			duree_tmp = duree_int(tmph1,tmph2);
			if(duree_tmp < best_duree)
			{
				meilleur_duree.id=tmp->t.id;
				meilleur_duree.gareDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.gareDepart));
				strcpy(meilleur_duree.gareDepart,tmp->t.gareDepart);
				meilleur_duree.gareArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.gareArrivee));
				strcpy(meilleur_duree.gareArrivee,tmp->t.gareArrivee);
				meilleur_duree.heureDepart = (char *) malloc(sizeof(char) * strlen(tmp->t.heureDepart));
				strcpy(meilleur_duree.heureDepart,tmp->t.heureDepart);
				meilleur_duree.heureArrivee = (char *) malloc(sizeof(char) * strlen(tmp->t.heureArrivee));
				strcpy(meilleur_duree.heureArrivee,tmp->t.heureArrivee);
				meilleur_duree.Prix=tmp->t.Prix;
				meilleur_duree.reduction = (char *) malloc(sizeof(char) * strlen(tmp->t.reduction));
				strcpy(meilleur_duree.reduction,tmp->t.reduction);

				best_duree = duree_tmp;
			}
			tmp = tmp->suiv;
		}
	}
	return meilleur_duree;
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
		while(tmp != NULL) //tant qu'on est pas à la fin de la liste
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

char * traiterRequete(char *requete_client)
{
	int choix1=-1, choix2=-1, i=0, bufsize = TMAX;
	llist liste = NULL;
	char *train = (char *)malloc(TMAX);
	char * buf=malloc(sizeof(char)*50), *horaire_deb = malloc(sizeof(char)*30),	*horaire_fin = malloc(sizeof(char)*30);
	char * retourner = malloc(sizeof(char)*500);
	char *ville_depart = malloc(sizeof(char)*50);
	char *ville_arrivee = malloc(sizeof(char)*50);
	char *tmp = malloc(sizeof(char)*50);
	InfosTrain tabTrains[21];

	FILE *f = fopen("../bin/Trains.txt", "r");
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
			strcpy(tmp, requete_client);
			choix1 = atoi(strtok(tmp, ";"));
			tmp = strtok(NULL, ";");
			strcpy(ville_depart,tmp);
			tmp = strtok(NULL, ";");
			strcpy(ville_arrivee,tmp);
			strtoupper(ville_depart);
			strtoupper(ville_arrivee);

			switch(choix1)
			{
				case 1:
				{
					buf = strtok(NULL, ";");
					strcpy(horaire_deb,buf);
					liste = trainSatisfaisant(tabTrains,ville_depart,ville_arrivee,horaire_deb);
					strcpy(retourner,train_liste(liste));
					break;
				}
				case 2:
				{

					tmp = strtok(NULL, ";");
					strcpy(horaire_deb,tmp);
					tmp = strtok(NULL, ";");
					strcpy(horaire_fin,tmp);
					liste = trancheHoraire_list(liste,ville_depart,ville_arrivee,horaire_deb,horaire_fin);
					strcpy(retourner,train_liste(liste));
					break;
				}
				case 3:
				{
					buf = strtok(NULL, ";");
					choix2 = atoi(buf);
					printf("choix 2 : %d \n", choix2);
					switch(choix2)
					{
						case 0 : 
						{
							liste = listeTousLesTrains(tabTrains,ville_depart,ville_arrivee);
							strcpy(retourner,train_liste(liste));
							break;
						}
						case 1 :
						{
							liste = listeTousLesTrains(tabTrains,ville_depart,ville_arrivee);
							strcpy(retourner,cast_train(prix_opti(liste)));
							break;
						}
						case 2 : 
						{
							liste = listeTousLesTrains(tabTrains,ville_depart,ville_arrivee);
							strcpy(retourner,cast_train(duree_opti(liste)));
							break;
						}
					}
					break;
				}
			}	
	}
	free(train);
	//fclose(f);
	return retourner;	
}
