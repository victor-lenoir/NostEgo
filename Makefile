CFLAGS=-W -Wall -Wextra -Werror
LINK=-lSDL -lSDL_image -lSDL_ttf
CC=g++

HEADERS=	 		\
src/game/game.hh 		\
src/interface/interface.hh

OBJS=				\
src/main.o			\
src/game/game.o	 		\
src/interface/interface.o

all: nostego

nostego: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o nostego

%.o: %.cc Makefile ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@
