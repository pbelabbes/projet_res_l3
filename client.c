#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define TVILLE 500

void fctclient (int p)
{
	char tab[255];

	scanf ("%s",tab);
	printf ("%s",tab);

	write (p,tab, sizeof (tab) );

}

//Prepare la requête à partir des données passées
void prepareRequest(char** datas,char* request, int taille){ // [code,ville ... ]

	char request_tmp[1000]="\0";
	int i = 0;
	for (i = 0; i < taille-1; ++i)
	{
		strcat(request_tmp,datas[i]);
		strcat(request_tmp,";");
	}

	strcat(request_tmp,datas[i]);
	strcpy(request,request_tmp);
}



void IHM ( ){
	int choix = -1, choix2 = -1;
	char ville_depart[TVILLE], ville_arrivee[TVILLE];
	char horaire[5], horaire_dep[5], horaire_fin[5];
	char  m_prix [5],d_optimum[5];
	char request[1000];
	printf ("Binvenue \n");
	printf("code 1 : Premier train existant : \n \t - Ville de depart \n \t - Ville d'arrivee \n \t- Horaire de depart\n\n");
	printf("code 2 : Liste des trains : \n \t - Ville de depart \n \t - Ville d'arrivee \n \t - Debut tranche horaire de depart \n \t - Fin tranche horaire de depart\n\n");
	printf("code 3 : Liste des trains  : \n \t - Ville de depart \n \t - Ville d'arrivee \n\n");
//printf("code 4 : Afficher le fichier trains.txt \n\n");
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
		printf("\nHoraire de depart (format hh:mm) : ");
		scanf("%s",horaire);
		

		char* datas_1[4] = {"1",ville_depart,ville_arrivee,horaire};

		prepareRequest(datas_1,request,4);
		printf("%s\n",request);
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

		char* datas_2[5]={"2",ville_depart,ville_arrivee,horaire_dep,horaire_fin};
		prepareRequest(datas_2,request,5);
		printf("%s\n", request);
		break;

		case 3:
		printf("Ville de depart : ");
		scanf("%s",ville_depart);
		printf("Ville d'arrivee : ");
		scanf("%s",ville_arrivee);

		char* datas_3[4]={"3",ville_depart,ville_arrivee,"0"};
		prepareRequest(datas_3,request,4);
		printf("%s\n", request);

		/* affichage */

		printf("Trier cette liste ? (0 si non) \n");
		printf("code 1 : Trie par rapport au meilleur prix \n");
		printf("code 2 : Trie par rapport au temps de trajet \n ");
		scanf("%d", &choix2);

		switch(choix2)
		{

			case 1:
			printf("%s\n","Choix n°1" ); 
			char* datas_4[4]={"3",ville_depart,ville_arrivee,"1"};
			prepareRequest(datas_4,request,4);
			printf("%s\n",request);
			break;
			case 2:
			printf("%s\n","Choix 2" );
			char* datas_5[4]={"3",ville_depart,ville_arrivee,"2"};
			prepareRequest(datas_5,request,4);
			printf("%s\n",request);

			break;
		}
		break;
		case 4 :
		system("cat trains.txt");
		printf("\n\n");
		break;
		default : 
		printf("Mauvais code \n\n");
		break;
	}        

}



int main(int argc,char *argv[]){

/* Creation de la requete */

	IHM();

/* Création de la socket */
	printf("%s\n","Création de la socket " );
	struct sockaddr_in s;
	int i;
	int p = socket(AF_INET,SOCK_STREAM,0);
	struct hostent *h ;
	char l[1000];

	int numPort;

//printf ("%s\n",argv[1]);
	printf ("%d\n",argc);


	if (argc > 1) 
		{numPort = atoi(argv[1]);}
	else { numPort = 27000;}
	
	s.sin_port = htons(numPort);
	s.sin_family = AF_INET;
	
	//s.sin_port = htons(27000);
	s.sin_addr.s_addr = htonl(INADDR_ANY);
	for(i=0;i<8;i++){
		s.sin_zero[i]=0;
	}


	/*recupération des information */
	// gethostname(l,1000);									
	h = gethostbyname("localhost");
	printf("hostname %s\n", h->h_name);

	memcpy(&s.sin_addr.s_addr, h->h_addr,h->h_length);


	/*demande de connexion  */
	printf("%s\n"," demande de connexion " );

	int erco = connect (p,(struct sockaddr*)&s, sizeof( struct sockaddr)); 
	if (erco == -1){
		printf("%s\n", "erreur de connexion" );

	}else printf("%s\n","connexion avec succès" );
	fctclient(p); 
	return 0;

}
