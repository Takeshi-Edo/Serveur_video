#####################################################################
#     Projet : Aide à la maitenance en réalité augmentée     	    #
#     Nom du Fichier : Makefile									 	#
#     Personnes : Takfarinas Kebci, Yann Nebout						#
#     Objectif(s) du programme : utiliser la caméra avec OpenCV     #
#	  Date de Début : 26 Février 2018								#
#	  Date de la dernière modification : 15 Mars 2018				#
#####################################################################

CC=gcc
PP=g++

SRCDIR=Src
HEADDIR=Include
EXECDIR=Bin
OBJDIR=Obj
# Option de compilation : 
#	 Wall : affiche les warnings
#	 Werror : warning = erreur
#	 Wextra : Ajoute des warning specifique en plus a Wall
#	 g : analyse gdb & valgrind
CFLAGS= -I$(HEADDIR) -Wall -c
CXXFLAGS= -I$(HEADDIR) -Wall -cpp
#LIBSGL= -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
#LIBSCV= `pkg-config opencv --cflags --libs`
# LIBS= -lpthread
# Executable
EXEC = Serveur Client

# Où trouver les différents sources *.cpp qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.cpp)
OBJ= $(SRC:$(SRCDIR)/%.cpp=%.o)

all: $(EXEC) .PHONY

Client: Client.o 
	$(CC) -o $@  $^ $(CFLAGS)
	
Serveur: Serveur.o
	$(CC) -o $@  $^ $(CFLAGS)
	

#RA_test: RA_CUBE.o Cube.o Carre.o Couleur.o
#	$(PP) -o $(EXECDIR)/$@  $^ $(CXXFLAGS) $(LIBS) $(LIBSCV) $(LIBSGL)
#	./$(EXECDIR)/$(EXEC)

# Création des différents *.o à partir des *.cpp
%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm -rf *.o *~
	
vclean:
	rm -rf $(EXEC)
	
.PHONY: clean
