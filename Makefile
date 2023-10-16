CC = gcc
CFLAGS = -g -Wall -Werror -O2
LDFLAGS = -lncurses

tetris: tcommons.o letters.o menus.o tscore.o tmap.o tblocks.o nextwin.o tetris.o

clean:
	rm -f tetris *.o
