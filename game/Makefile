CFLAGS=-W -Wall -Wextra -std=c++0x
LINK=-lSDL -lSDL_image -lSDL_ttf -lSDL_gfx
CC=g++

all: Makefile.inc nostego

clean:
	rm -f `find . -name '*.o'`
	rm -f `find . -name '*.~'`
	rm -f `find . -name '*.#'`
	rm -f Makefile.inc
	rm -f nostego

Makefile.inc:
	./configure

include Makefile.inc

nostego: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o nostego

%.o: %.cc Makefile ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@
