CFLAGS=-W -Wall -Wextra -Werror -Wfloat-equal -Wshadow -Wpointer-arith \
-Wcast-qual -Wcast-align -Wmissing-declarations -Wunused -Winline -pedantic \
-Wuninitialized -Winit-self
IFLAGS=-I src/
LINK=-lsfml-graphics
CC=g++

all: Makefile.inc nostego

clean:
	rm -f `find . -name '*.o'`
	rm -f `find . -name '*~'`
	rm -f `find . -name '*#'`
	rm -f Makefile.inc
	rm -f nostego

Makefile.inc:
	./configure

include Makefile.inc

nostego: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o nostego
