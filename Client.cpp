/*
+-----------------------------------------------------------------------------------------------+
|     Projet : Aide à la maitenance en réalité augmentée                                        |
|     Nom du Fichier : Client.cpp                                                               |
|     Personnes : Takfarinas Kebci, Yann Nebout	Aurélien Vernizeau Arthur Cayet Lucas Legon     |
|     Objectif(s) du programme : Permettre crée un client pour un serveur                       |
|     Date de Début : 26 Février 2018                                                           |
|     Date de la dernière modification : 31 Mai 2018                                            |
+-----------------------------------------------------------------------------------------------+
*/

#include "Client.hpp"

using namespace std;

Client::Client(){
	name = "Client";
	hotspot_serveur = "localhost";
	id = 1;
	socket_text = 0;
}

Client::Client(string n, int identity, string hotspot){
	name = n;
	id = identity;
	hotspot_serveur = hotspot;
}

Client::Client(const Client &c){
	name = c.name;
	id = c.id;
	commentaire = c.commentaire;
	hotspot_serveur = c.hotspot_serveur;
}

Client::~Client(){}

void Client::setName(string n){name = n;}
void Client::setId(int identity){id = identity;}
void Client::setSockets(int s_text){socket_text = s_text;}

string Client::getName() const {return name;}
int Client::getIdentity() const {return id;}
int Client::getSocketT() const {return socket_text;}

void Client::createSocketText(){
	socket_text = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *hostinfo;

	if(socket_text == INVALID_SOCKET){
		perror("socket()");
		exit(errno);
	}

	hostinfo = gethostbyname(hotspot_serveur.c_str());
	if (hostinfo == NULL){
		fprintf (stderr, "Unknown host %s.\n", hotspot_serveur.c_str());
		exit(EXIT_FAILURE);
	}

	SOCKADDR_IN sin = {0};
	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	
	connectSocketText(sin);
}

void Client::connectSocketText(SOCKADDR_IN sin){
	if(connect(socket_text,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR){
    	perror("connect()");
    	exit(errno);
	}
}

void Client::envoiText(const char *buffer){
	if(send(socket_text, buffer, strlen(buffer), 0) < 0){
		perror("send()");
		exit(errno);
	}
}

int Client::receptionText(char * buffer){
	int n = 0;

	if((n = recv(socket_text, buffer, BUF_SIZE - 1, 0)) < 0){
		perror("recv()");
		exit(errno);
	}
	buffer[n] = 0;

	return n;
}

void Client::fermetureSocketText(){
	close(socket_text);
}

void Client::mySocket(){
	createSocketText();
	char buffer[BUF_SIZE];
	const char* nom = name.c_str();
	fd_set rdfs;
	/* send our name */
	envoiText(nom);

	while(1){
		FD_ZERO(&rdfs);
	/* add STDIN_FILENO */
		FD_SET(STDIN_FILENO, &rdfs);
	/* add the socket */
		FD_SET(socket_text, &rdfs);
		if(select(socket_text + 1, &rdfs, NULL, NULL, NULL) == -1){
			perror("select()");
			exit(errno);
		}

		/* something from standard input : i.e keyboard */
		if(FD_ISSET(STDIN_FILENO, &rdfs)){
			fgets(buffer, BUF_SIZE - 1, stdin);{
				char *p = NULL;
				p = strstr(buffer, "\n");
				if(p != NULL){
				   *p = 0;
				}
				else{
				   /* fclean */
				   buffer[BUF_SIZE - 1] = 0;
				}
			}
			envoiText(buffer);
		}
		else if(FD_ISSET(socket_text, &rdfs)){
			int n = receptionText(buffer);
			/* server down */
			if(n == 0){
				printf("Server disconnected !\n");
				break;
			}
			puts(buffer);
		}
	}

	fermetureSocketText();
}

int main(int argc, char** argv){
	Client client(argv[1], 1, argv[2]);
	client.mySocket();
	
	return 0;
}
