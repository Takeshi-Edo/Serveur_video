/*
+-----------------------------------------------------------------------------------------------+
|     Projet : Aide à la maitenance en réalité augmentée                                        |
|     Nom du Fichier : Serveur.hpp                                                              |
|     Personnes : Takfarinas Kebci, Yann Nebout	Aurélien Vernizeau Arthur Cayet Lucas Legon     |
|     Objectif(s) du programme : Permettre crée un serveur                                      |
|     Date de Début : 26 Février 2018                                                           |
|     Date de la dernière modification : 31 Mai 2018                                            |
+-----------------------------------------------------------------------------------------------+
*/

#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include "Client_Serveur.hpp"
#include "util.hpp"

class Serveur{
	protected:
		int socket_text;
		int max_client;
		
	public:
		Serveur();
		Serveur(int max);
		Serveur(const Serveur& s);
		~Serveur();
		
		void setSockets(int s_text);
		
		int getSocketT() const;
		
		void createSocketText();
		void connectSocketText(SOCKADDR_IN sin);
		void envoiTextAll(Clientserveur *clients, Clientserveur sender, int actual, const char *buffer, char from_server);
		void envoiText(int sock, const char *buffer);
		int receptionText(int sock, char* buffer);
		void fermetureSocketText();
		void mySocket();
		
		void clearClient(Clientserveur* client, int actual);
		void removeClient(Clientserveur* client, int to_remove,int* actual);
};

#endif
