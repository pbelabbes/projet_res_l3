CC=gcc
FLAGS= -Wall
EXEC=serveur client
SERVEUR = serveur/
CLIENT = client/
SRC=sources/
HDR=headers/
BIN=bin/




all : $(EXEC)

serveur : serveur.o 
	$(CC) -o $(SERVEUR)$(BIN)$@ $(SERVEUR)$(BIN)$^ $(FLAGS)

serveur.o : 
	$(CC) -o $(SERVEUR)$(BIN)$@ -c $(SERVEUR)$(SRC)serveur.c -I $(SERVEUR)$(HDR) $(FLAGS)

client : client.o
	$(CC) -o $(CLIENT)$(BIN)$@ $(CLIENT)$(BIN)$^ $(FLAGS)

client.o :  
	$(CC) -o $(CLIENT)$(BIN)$@ -c $(CLIENT)$(SRC)client.c -I $(CLIENT)$(HDR) $(FLAGS)

clean : 
	rm -rf $(SERVEUR)$(BIN)*.o $(CLIENT)$(BIN)*.o

mrproper : clean
	rm -rf $(SERVEUR)$(BIN)serveur $(CLIENT)$(BIN)client 