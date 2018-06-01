/*
+-----------------------------------------------------------------------------------------------+
|     Projet : Aide à la maitenance en réalité augmentée                                        |
|     Nom du Fichier : Client_Serveur.hpp                                                       |
|     Personnes : Takfarinas Kebci, Yann Nebout	Aurélien Vernizeau Arthur Cayet Lucas Legon     |
|     Objectif(s) du programme : Définir un client du point de vu du serveur                    |
|     Date de Début : 26 Février 2018                                                           |
|     Date de la dernière modification : 31 Mai 2018                                            |
+-----------------------------------------------------------------------------------------------+
*/

#ifndef CLIENT_SERVEUR_HPP
#define CLIENT_SERVEUR_HPP

#include "util.hpp"

typedef struct client_serveur{
	int csocket;
	char name[BUF_SIZE];
} Clientserveur;

#endif
