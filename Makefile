#OBJS: Fichiers à compiler
OBJS = main.cc


FLAGS = -Wall -lSDL2 -o

#OUTPUT: Nom du fichier de sortie
OUTPUT = a.out

#Compilation 
all : $(OBJS)
	g++ $(OBJS) $(FLAGS) $(OUTPUT)
