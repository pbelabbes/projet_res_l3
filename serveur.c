/*auteurs soussi sirine, pierre baudriller , romain brunet , pierre belabbes  */
#include "serveur.h"

/*
struct in_addr{
	u_long s_addr;
};


struct sockaddr_in{
	short sin_family;lui donner la valeur AF_INET
	u_short sin_port;Numéro de port
	struct in_addr sin_addr;//ADresse de la machine
	char sin_zero[8];//par défaut = 0
};*/


int rendreService(int desc){

	printf("%s\n","Prêt à rendre service" );
	char recep[255];
	int stop = 1;

	while(stop > 0){
		stop = read(desc, recep, 255);
		if(stop) printf("%s\n",recep); //1;params
		//char* traiterRequete(char* requete);
		//char* afficher_train( char* gare_depart, char* gare_arrivee, char* horaire);
		//char* afficher_trains_tranche( char* gare_depart, char* gare_arrivee, char* horaire_depart, char* horaire_arrivee);
		//char* afficher_horaires( char* gare_depart, char* gare_arrivee, int tri)	; ( trie : 0 -> pas de trie, 1 -> tri prix, 2 -> tri durée)
		write(desc,recep,255);
	}

	exit(0);
}


void finfils(int sig){

	wait(0);
}

//Pour tester 'nc 127.0.0.1 27000'
int main(int argc,char *argv[]){

	/* Préparation de la gestion des fils*/ 

	struct sigaction a;

	a.sa_handler = finfils;

	a.sa_flags = SA_RESTART;

	sigaction(SIGCHLD, &a, NULL);

	/* Création de la socket d'écoute */

	printf("%s\n","Création de la socket d'écoute" );
	struct sockaddr_in s;
	int i;
	int p = socket(AF_INET,SOCK_STREAM,0);
	
	int numPort = (argc > 1 )?atoi(argv[1]):27000;
	printf("%s%d\n","connexion au port : ",numPort );
	s.sin_family = AF_INET;
	s.sin_port = htons(numPort);
	s.sin_addr.s_addr = htonl(INADDR_ANY);
	for(i=0;i<8;i++){
		s.sin_zero[i]=0;
	}
	
	/*Attachement de la socket d'écoute*/
	printf("%s\n","bind de la socket d'écoute" );
	bind(p,(struct sockaddr*) &s, sizeof(s));
	
	/*Ouverture de service sur la socket d'écoute */

	listen(p,4);
	/*Boucle infinie*/
	struct sockaddr_in client;
	int c_length;
	while(1){
		printf("%s\n","Début d'écoute" );
		int servSock = accept(p, (struct sockaddr*) &client, &c_length);

		printf("%s\n","connecté au client" );
		switch(fork()){

			//Gestion d'erreur
			case -1 :
				perror ("fork") ;
       			exit (-1) ;
			break;

			//Fils
			case 0 : 
			close (p);
			rendreService(servSock);
		}

		close(servSock); 
	}
	return 0;
}


