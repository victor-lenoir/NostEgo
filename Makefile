CFLAGS=-W -Wall -Wextra -Werror
LINK=-lSDL -lSDL_image -lSDL_ttf
CC=g++

all: Makefile.inc nostego

Makefile.inc:
	./configure

include Makefile.inc

nostego: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o nostego

%.o: %.cc Makefile ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@
