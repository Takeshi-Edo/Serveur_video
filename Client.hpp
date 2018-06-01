/*
+-----------------------------------------------------------------------------------------------+
|     Projet : Aide à la maitenance en réalité augmentée                                        |
|     Nom du Fichier : Client.hpp                                                               |
|     Personnes : Takfarinas Kebci, Yann Nebout	Aurélien Vernizeau Arthur Cayet Lucas Legon     |
|     Objectif(s) du programme : Permettre crée un client pour un serveur                       |
|     Date de Début : 26 Février 2018                                                           |
|     Date de la dernière modification : 31 Mai 2018                                            |
+-----------------------------------------------------------------------------------------------+
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "util.hpp"

class Client{
	protected:
		std::string name;
		std::string hotspot_serveur;
		int id;
		//cv::Mat image;
		std::string commentaire;
		int socket_text;
		//int socket_video;
		
	public:
		Client();
		Client(std::string n, int identity, std::string hotspot);
		Client(const Client &c);
		~Client();
		
		void setName(std::string n);
		void setId(int identity);
		//void setImage(cv::Mat im);
		void setSockets(int s_text);
		
		std::string getName() const;
		int getIdentity() const;
		//cv::Mat getImage() const;
		int getSocketT() const;
		//int getSocketV() const;		
		
		//void createSocketVideo();
		//void connectSocketVideo();
		//void envoiVideo();
		//void receptionVideo();
		void createSocketText();
		void connectSocketText(SOCKADDR_IN sin);
		void envoiText(const char *buffer);
		int receptionText(char* buffer);
		void fermetureSocketText();
		void mySocket();
};

#endif
