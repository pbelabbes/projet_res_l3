
#include "client.h"


// l'envoi et la réception des requêtes
char* sendRequest (int p,char *request)
{
	char* response = malloc(255);
	write (p,request, strlen(request));
	printf("%s\n","En attente de réponse ..." );
	read(p,response,255);
	return response;
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


// IHM pour récupère les informations de l'uilisateur
void IHM ( int p){
	int choix = -1, choix2 = -1;
	char ville_depart[TVILLE], ville_arrivee[TVILLE];
	char horaire[5], horaire_dep[5], horaire_fin[5];
	char request[1000];
	char* response;

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
		scanf("%[^\n]",ville_depart);
		getchar();
		printf("\nVille d'arrivee : ");
		getchar();
		scanf("%[^\n]",ville_arrivee);
		printf("\nHoraire de depart (format hh:mm) : ");
		getchar();
		scanf("%[^\n]",horaire);


		char* datas_1[4] = {"1",ville_depart,ville_arrivee,horaire};

		prepareRequest(datas_1,request,4);
		printf("%s\n",request);
		response = sendRequest(p,request);
		printf("%s\n",response );
		break;



		case 2:
		printf("Ville de depart : ");
		getchar();
		scanf("%[^\n]",ville_depart);
		printf("\nVille d'arrivee : ");
		getchar();
		scanf("%[^\n]",ville_arrivee);
		printf("%[^\n]Debut tranche horaire de depart (format xxhyy) : ");
		getchar();
		scanf("%[^\n]",horaire_dep);
		printf("\nFIN tranche horaire de depart (format xxhyy) : ");
		getchar();
		scanf("%[^\n]",horaire_fin);

		char* datas_2[5]={"2",ville_depart,ville_arrivee,horaire_dep,horaire_fin};
		prepareRequest(datas_2,request,5);
		response = sendRequest(p,request);
		printf("%s\n",response );
		break;

		case 3:
		printf("Ville de depart : ");
		getchar();
		scanf("%[^\n]",ville_depart);
		printf("Ville d'arrivee : ");
		getchar();
		scanf("%[^\n]",ville_arrivee);

		char* datas_3[4]={"3",ville_depart,ville_arrivee,"0"};
		prepareRequest(datas_3,request,4);
		response = sendRequest(p,request);
		printf("%s\n",response );
		
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
			response = sendRequest(p,request);
			printf("%s\n",response );	
			break;
			case 2:
			printf("%s\n","Choix 2" );
			char* datas_5[4]={"3",ville_depart,ville_arrivee,"2"};
			prepareRequest(datas_5,request,4);
			printf("%s\n",request);
			response = sendRequest(p,request);
			printf("%s\n",response );
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


/* Création de la socket */
	printf("%s\n","Création de la socket " );
	struct sockaddr_in s;
	int i;
	int p = socket(AF_INET,SOCK_STREAM,0);
	struct hostent *h ;

	int numPort;

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


	/*demande de connexion avec le serveur */
	printf("%s\n"," demande de connexion " );

	int erco = connect (p,(struct sockaddr*)&s, sizeof( struct sockaddr)); 
	if (erco == -1){
		printf("%s\n", "erreur de connexion" );

	}else printf("%s\n","connexion avec succès" );
	
	IHM(p);
	return 0;

}
