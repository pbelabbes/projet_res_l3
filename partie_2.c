#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TVILLE 100 /*faire des malloc ? */
#define TMAX 100




int duree(char[TAILLE_MAX] h_debut, char[TAILLE_MAX] h_fin)
{
	char *h1, *h2, *min1, *min2;
	int duree;

	*h1 = strtok(h_debut, ":");
	*min1 = strtok(NULL, ":");

	*h2 = strtok(h_fin, ":");
	*min2 = strtok(NULL, ":");

	// gerer si train arrive tot le matin

        duree = h2 - h1;
        return duree;
}




int compare_ville(char *ville1, char *ville2)
{
	return strcmp(ville1, ville2);	
}

void villes(FILE *f, char *user_depart, char *user_arrivee)
{
	
	char *train = NULL, *depart, *arrivee;
	size_t bufsize = TMAX;
	int res;

	train = (char *)malloc(TMAX);

	while(!feof(f))
  	{
		getline(&train,&bufsize , f);
		depart = strtok(train, ";");
		printf("%s \n",depart);
	
		arrivee= strtok(NULL, ";");
		printf("%s \n",arrivee);

		res =  compare_ville(user_depart, depart);
		printf("%d \n",res);
	}
	fclose(f);	
}

int main ()
{
	FILE *f = NULL;
	int choix = -1, choix2 = -1;
	char ville_depart[TVILLE], ville_arrivee[TVILLE];
	char horaire[5], horaire_dep[5], horaire_fin[5];


	f=fopen("Trains.txt", "r");
	if(f == NULL)
	{
		printf("Erreur ouverture fichier \n");
		exit(0);
	}

	printf("Bienvenue !\n\n");
	while(choix != 0)
	{
		printf("code 1 : Premier train existant : \n \t - Ville de depart \n \t - Ville d'arrivee \n \t - Horaire de depart\n\n");
		printf("code 2 : Liste des trains : \n \t - Ville de depart \n \t - Ville d'arrivee \n \t - Debut tranche horaire de depart \n \t - Fin tranche horaire de depart\n\n");
		printf("code 3 : Liste des trains  : \n \t - Ville de depart \n \t - Ville d'arrivee \n\n");
		printf("code 4 : Afficher le fichier trains.txt \n\n");
		printf("Que voulez vous obtenir ? (0 pour quitter) : ");
		scanf("%d",&choix);
		printf("\n");

		switch(choix)
		{
			case 0: 
				printf("A bientot ! \n");
				exit(1);
			case 1:
				printf("Ville de depart : ");
				scanf("%s",ville_depart);
				printf("\nVille d'arrivee : ");
				scanf("%s",ville_arrivee);
				printf("\nHoraire de depart (format xxhyy) : ");
				scanf("%s",horaire);



				villes(f);

				break;

			case 2:
				printf("Ville de depart : ");
				scanf("%s",ville_depart);
				printf("\nVille d'arrivee : ");
				scanf("%s",ville_arrivee);
				printf("\nDebut tranche horaire de depart (format xxhyy) : ");
				scanf("%s",horaire_dep);
				printf("\nFIN tranche horaire de depart (format xxhyy) : ");
				scanf("%s",horaire_fin);
				break;

			case 3:
				printf("Ville de depart : ");
				scanf("%s",ville_depart);
				printf("Ville d'arrivee : ");
				scanf("%s",ville_arrivee);
				/* affichage */

				printf("Trier cette liste ? (0 si non) \n");
				printf("code 1 : Trie par rapport au meilleur prix \n");
				printf("code 2 : Trie par rapport au temps de trajet \n ");
				scanf("%d", &choix2);
				
				/*switch(choix2)
				{
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
				}*/
			case 4 :
				system("cat trains.txt");
				printf("\n\n");
				break;
			default : 
				printf("Mauvais code \n\n");
				break;
		}	
		
	}
	
	return 0;

}

