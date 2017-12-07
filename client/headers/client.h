#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define TVILLE 500


char* sendRequest (int p,char *request);
void prepareRequest(char** datas,char* request, int taille);
void IHM ( int p);
	
#endif