all : serveur client

client : client.o
	gcc -o client client.o

client.o : client.c
	gcc -o client.o -c client.c -Wall

serveur.o : serveur.c
	gcc -o serveur.o -c serveur.c -Wall