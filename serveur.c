#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <signal.h>
//#include <wait.h>
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

	char* recep;
	
	while(1){
		read(desc, recep, 255);
		printf("%s\n",recep);
	}

}


int main(int argc,char *argv[]){
	/* Création de la socket d'écoute */

	printf("%s\n","Création de la socket d'écoute" );
	struct sockaddr_in s;
	int i;
	int p = socket(AF_INET,SOCK_STREAM,0);
	s.sin_family = AF_INET;
	s.sin_port = htons(27000);
	s.sin_addr.s_addr = htonl(INADDR_ANY);
	for(i=0;i<8;i++){
		s.sin_zero[i]=0;
	}
	
	/*Attachement de la socket d'écoute*/
	printf("%s\n","bind de la socket d'écoute" );
	bind(p,(struct sockaddr*) &s, sizeof(s));
	
	/*Ouverture de service sur la socket d'écoute */

	printf("%s\n","Début d'écoute" );
	listen(p,4);
	/*Boucle infinie*/
	struct sockaddr_in client;
	int c_length;
	while(1){
		int servSock = accept(p, (struct sockaddr*) &client, &c_length);

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


