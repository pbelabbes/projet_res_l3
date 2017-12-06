#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


void fctclient (int p)
{
char tab[255];

scanf ("%s",tab);
printf ("%s",tab);

write (p,tab, sizeof (tab) );

}


int main(int argc,char *argv[]){

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
