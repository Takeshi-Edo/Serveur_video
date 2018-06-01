/*
+-----------------------------------------------------------------------------------------------+
|     Projet : Aide à la maitenance en réalité augmentée                                        |
|     Nom du Fichier : Serveur.cpp                                                              |
|     Personnes : Takfarinas Kebci, Yann Nebout	Aurélien Vernizeau Arthur Cayet Lucas Legon     |
|     Objectif(s) du programme : Permettre crée un client pour un serveur                       |
|     Date de Début : 26 Février 2018                                                           |
|     Date de la dernière modification : 31 Mai 2018                                            |
+-----------------------------------------------------------------------------------------------+
*/

#include "Serveur.hpp"

using namespace std;

Serveur::Serveur(){
	socket_text = 0;
	max_client = 5;
}

Serveur::Serveur(int max){
	socket_text = 0;
	max_client = max;
}

Serveur::Serveur(const Serveur& s){
	socket_text = s.socket_text;
	max_client = s.max_client;
}

Serveur::~Serveur(){}

void Serveur::setSockets(int s_text){socket_text = s_text;}

int Serveur::getSocketT() const {return socket_text;}

void Serveur::createSocketText(){
	socket_text = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };
	if(socket_text == INVALID_SOCKET){
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;

	if(bind(socket_text,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR){
		perror("bind()");
		exit(errno);
	}

	connectSocketText(sin);
}

void Serveur::connectSocketText(SOCKADDR_IN sin){
	if(listen(socket_text, max_client) == SOCKET_ERROR){
		perror("listen()");
		exit(errno);
	}
}

void Serveur::envoiText(int sock, const char *buffer){
	if(send(sock, buffer, strlen(buffer), 0) < 0){
		perror("send()");
		exit(errno);
	}
}

int Serveur::receptionText(int sock, char * buffer){
	int n = 0;

	if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0){
		perror("recv()");
		exit(errno);
	}

	buffer[n] = 0;

	return n;
}

void Serveur::fermetureSocketText(){
	close(socket_text);
}

void Serveur::envoiTextAll(Clientserveur *clients, Clientserveur sender, int actual, const char *buffer, char from_server){
	int i = 0;
	char message[BUF_SIZE];
	message[0] = 0;
	for(i = 0; i < actual; i++){
	/* we don't send message to the sender */
		if(sender.csocket != clients[i].csocket){
			if(from_server == 0){
				strncpy(message, sender.name, BUF_SIZE - 1);
				strncat(message, " : ", sizeof message - strlen(message) - 1);
			}
			strncat(message, buffer, sizeof message - strlen(message) - 1);
			envoiText(clients[i].csocket, message);
		}
	}
}

void Serveur::clearClient(Clientserveur* client, int actual){
	int i = 0;
	for(i = 0; i < actual; i++){
		close(client[i].csocket);
	}
}

void Serveur::removeClient(Clientserveur* client, int to_remove,int* actual){
	/* we remove the client in the array */
	memmove(client + to_remove, client + to_remove + 1, (*actual - to_remove - 1) * sizeof(Clientserveur));
	/* number client - 1 */
	(*actual)--;
}

void Serveur::mySocket(){
	createSocketText();

	fd_set rdfs;
	/* send our name */
	char buffer[BUF_SIZE];
	/* the index for the array */
	int actual = 0;
	int max = socket_text;
	/* an array for all clients */
	Clientserveur clients[max_client];


	while(1){
		int i = 0;
		FD_ZERO(&rdfs);

		/* add STDIN_FILENO */
		FD_SET(STDIN_FILENO, &rdfs);
	
		/* add the connection socket */
		FD_SET(socket_text, &rdfs);

		/* add socket of each client */
		for(i = 0; i < actual; i++){
			FD_SET(clients[i].csocket, &rdfs);
		}

		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1){
			perror("select()");
			exit(errno);
		}

		/* something from standard input : i.e keyboard */
		if(FD_ISSET(STDIN_FILENO, &rdfs)){
			/* stop process when type on keyboard */
			break;
		}
		else if(FD_ISSET(socket_text, &rdfs)){
		/* new client */ 
			SOCKADDR_IN csin = { 0 };
			socklen_t sinsize = sizeof(csin);
			int csock = accept(socket_text, (SOCKADDR *)&csin, &sinsize);
			if(csock == SOCKET_ERROR){
				perror("accept()");
				continue;
			}
			/* after connecting the client sends its name */
			if(receptionText(csock, buffer) == -1){
				/* disconnected */
				continue;
			}
			/* what is the new maximum fd ? */
			max = csock > max ? csock : max;
	
			FD_SET(csock, &rdfs);
			Clientserveur c = { csock };
			strncpy(c.name, buffer, BUF_SIZE - 1);
			cout << c.name << endl;
			cout << c.csocket << endl;
			clients[actual] = c;
			cout << clients[actual].name << endl;
			cout << clients[actual].csocket << endl;
			actual++;
		}
		else{
			int i = 0;
			
			for(i = 0; i < actual; i++){
				/* a client is talking */
				if(FD_ISSET(clients[i].csocket, &rdfs)){
					Clientserveur client = clients[i];
					int c = receptionText(clients[i].csocket, buffer);
					/* client disconnected */
					if(c == 0){
						close(clients[i].csocket);
						removeClient(clients, i, &actual);
						strncpy(buffer, client.name, BUF_SIZE - 1);
						strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
						envoiTextAll(clients, client, actual, buffer, 1);
			   		}
			   		else {
						envoiTextAll(clients, client, actual, buffer, 0);
			 		}
			 		break;
				}
			}
		}
	}

	clearClient(clients, actual);

	fermetureSocketText();
}

int main(int argc, char** argv){
	
	Serveur serveur(5);
	serveur.mySocket();
	
	return 0;
}
