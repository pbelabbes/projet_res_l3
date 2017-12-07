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

/**
	Recoit les données du client et envoit la réponse vers le client
*/
int rendreService(int desc){

	printf("%s\n","Prêt à rendre service" );
	char recep[255];
	int stop = 1;

	while(stop > 0){
		stop = read(desc, recep, 255);
		if(stop) printf("%s\n",recep); //1;params
		//char* traiterRequete(char* requete);
		write(desc,recep,255);
	}

	exit(0);
}

/**
	handler réagissant au signal de mort d'un fils pour que le père acquiesse sa mort
*/
void finfils(int sig){

	wait(0);
}


int main(int argc,char *argv[]){

	/* Mise en place du handler */ 

	struct sigaction a;

	a.sa_handler = finfils;

	a.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &a, NULL) == -1){
		perror("Erreur de gestion de signal");
		exit(1);
	}

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
	
	/* binding de la socket d'écoute */

	printf("%s\n","bind de la socket d'écoute" );
	if (bind(p,(struct sockaddr*) &s, sizeof(s)) == -1){
		perror("Erreur de binding");
		exit(1);
	}

	
	/*Ouverture de service sur la socket d'écoute */

	if (listen(p,4)){
		perror("Erreur de mise en écoute");
		exit(1);
	}


	/*Boucle infinie*/
	struct sockaddr_in client;
	unsigned int c_length;

	while(1){
		printf("%s\n","Début d'écoute" );

		int servSock = accept(p, (struct sockaddr*) &client, &c_length);

		printf("%s\n","connecté au client" );
		switch(fork()){

			//Gestion d'erreur
			case -1 :
				perror ("fork") ;
       			exit (1) ;
			break;

			//Fils
			case 0 : 
			if (close (p) == -1 ){
				perror ("Erreur de fermeture de la socket d'écoute") ;
       			exit (1) ;
			}
			rendreService(servSock);
		}

		if (close(servSock)){
			perror("Erreur de fermeture de la socket de service");
			exit(1);
		} 
	}
	return 0;
}


