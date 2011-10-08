CFLAGS=-W -Wall -Wextra -Werror
LINK=-lSDL
CC=g++
OBJS=		\
src/main.o	\
src/game/game.o

all: nostego

nostego: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o nostego

%.o: %.cc Makefile
	${CC} -c ${CFLAGS} $< -o $@
