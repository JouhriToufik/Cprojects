all: ddgm.out
ddg.o: ddg.c ddg.h
	gcc -std=c89 -pedantic -Wall -Werror -g `xml2-config --cflags` -c -o ddg.o ddg.c
player.o: player.c player.h ddg.o
	gcc -std=c89 -pedantic -Wall -Werror -g `xml2-config --cflags` -c -o player.o player.c
ddgm.out: ddgm.c player.o ddg.o
	gcc -std=c89 -pedantic -Wall -Werror -g  -o ddgm.out ddgm.c ddg.o player.o `xml2-config --cflags` `xml2-config --libs`
clean:
	rm -fv *.o *.out
