CC = gcc
CFLAGS = -g -Wall -Werror -O2
LDFLAGS = -lncurses

objects = tcommons.o letters.o menus.o tscore.o tmap.o tblocks.o nextwin.o

tetris: $(objects) tetris.o tests
	./tests
	rm -f tests tests.o
	$(CC) $(LDFLAGS) $(objects) tetris.o -o tetris

tests: $(objects) tests.o

$(objects) tetris.o tests.o: %.o: %.c

.PHONY: clean
clean:
	rm -f tetris tests *.o
