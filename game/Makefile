CFLAGS=-W -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith \
-Wcast-qual -Wcast-align -Wmissing-declarations -Wunused -Winline -pedantic \
-Wuninitialized -Winit-self

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
