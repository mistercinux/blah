CXX=g++
CXXFLAGS=-Wall -std=c++11
LIBS=-lSDL2 -lSDL2_image

# Autre possibilité: tu as une variable dans laquelle tu listes tes sources
SOURCES=main.cc vaisseau.cc rocket.cc gestion_sdl.cc
# et tu a une autre variable qui est initialisée à ta liste des sources mais en changeant l'extension (on passe de .cc à .o)
# si jamais dans $(SOURCES) il y a autre chose qu'un .cc, il sera présent dans $(OBJECTS) sans aucune modification de nom.
OBJECTS=$(SOURCES:.cc=.o)

all: blah

# Et comme dépendance, on peut bien sûr avoir des variables !
blah: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

clean:
	rm -f *.o

distclean: clean
	rm -f blah

