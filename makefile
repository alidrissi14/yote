CC=gcc
CFLAGS=-Wall
# LIBS=-lSDL2 -lSDL2_image -lm
LIBS=-lSDLmain -lSDL `sdl-config --cflags` -lSDL_image -lSDL_ttf
FILES=main.c game.c affichage.c
HEADERS=main.h game.h affichage.h
DIR=build

all: $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(FILES) -o yote $(LIBS)
	./yote

yote: $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(FILES) -o yote $(LIBS)

exec:
	./yote

clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}
