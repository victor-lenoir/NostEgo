CFLAGS=-W -Wall -Wextra -Werror -Wfloat-equal -Wshadow -Wpointer-arith \
-Wcast-qual -Wcast-align -Wmissing-declarations -Wunused -Winline -pedantic \
-Wuninitialized -Winit-self
IFLAGS=-I src/
LINK=-lsfml-graphics -lsfml-network
CC=g++

all: Makefile.inc nostego nostego_server

clean:
	rm -f `find . -name '*.o'`
	rm -f `find . -name '*~'`
	rm -f `find . -name '*#'`
	rm -f Makefile.inc
	rm -f nostego nostego_server

Makefile.inc:
	./configure

include Makefile.inc

nostego_server: ${OBJS} src/server/main.o
	${CC} ${CFLAGS} ${LINK} $^ -o nostego_server

nostego: ${OBJS} src/main.o
	${CC} ${CFLAGS} ${LINK} $^ -o nostego
