#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>





int main(int argc,char *argv[]){
	
/* Création de la socket */
printf("%s\n","Création de la socket d'écoute" );
	struct sockaddr_in s;
	int i;
	int p = socket(AF_INET,SOCK_STREAM,0);
	struct hostent *h ;
	

	s.sin_family = AF_INET;
	s.sin_port = htons(27000);
	s.sin_addr.s_addr = htonl(INADDR_ANY);
	for(i=0;i<8;i++){
		s.sin_zero[i]=0;
	}


	/*recupération des information */
	h =gethostbyname (argv[1]);
	memcpy(&s.sin_addr.s_addr, h->h_addr, sizeof(struct hostent));


	/*demande de connexion  */
	printf("%s\n"," demande de connexion " );
	connect (p,(struct sockaddr*)&s, sizeof s);




}
