
CC=i586-mingw32msvc-g++
RES=i586-mingw32msvc-windres

CFLAGS= -I/usr/i586-mingw32msvc/include 
LDFLAGS= -L/usr/i586-mingw32msvc/lib  -mwindows -lddraw -ldinput -ldsound -ldxguid -luser32 -lgdi32 -lwsock32 -lwinmm

FLIST= start.cpp soundhandle.cpp ParticleHandler.cpp gameover.cpp gintro.cpp grandma.cpp hero.cpp masterx.cpp mastermain.cpp intro.cpp game.cpp about.cpp options.cpp
LIBLIST=start.o soundhandle.o ParticleHandler.o gameover.o gintro.o grandma.o hero.o rez.o masterx.o mastermain.o intro.o game.o about.o options.o




all:
	$(RES) Script1.rc -o rez.o   
	$(CC) -Wno-deprecated -Wno-write-strings $(CFLAGS) $(FLIST) -c
	$(CC) -Wno-deprecated -Wno-write-strings $(LIBLIST) $(LDFLAGS) -o masterkong2d.exe
clean:
	rm -rf *.o *~
