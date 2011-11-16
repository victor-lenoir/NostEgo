CFLAGS=-W -Wall -Wextra -Werror -std=c++0x
LINK=-lSDL -lSDL_image -lSDL_ttf
CC=g++

all: Makefile.inc nostego

clean:
	rm -f `find . -name '*.o'`
	rm Makefile.inc
	rm nostego

Makefile.inc:
	./configure

include Makefile.inc

nostego: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o nostego

%.o: %.cc Makefile ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@
