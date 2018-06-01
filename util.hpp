/*
+-----------------------------------------------------------------------------------------------+
|     Projet : Aide à la maitenance en réalité augmentée                                        |
|     Nom du Fichier : util.hpp                                                                 |
|     Personnes : Takfarinas Kebci, Yann Nebout	Aurélien Vernizeau Arthur Cayet Lucas Legon     |
|     Objectif(s) du programme : librairies utiles                                              |
|     Date de Début : 26 Février 2018                                                           |
|     Date de la dernière modification : 31 Mai 2018                                            |
+-----------------------------------------------------------------------------------------------+
*/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <string>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define CRLF	 "\r\n"
#define PORT	 1977
#define BUF_SIZE 1024

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif
