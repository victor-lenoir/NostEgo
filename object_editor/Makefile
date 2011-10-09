CFLAGS=-W -Wall -Wextra -Werror -std=c++0x
LINK=
CC=g++

all: Makefile.inc editor

clean:
	rm -f `find . -name '*.o'`
	rm -f Makefile.inc
	rm -f editor

Makefile.inc:
	./configure

include Makefile.inc

editor: ${OBJS}
	${CC} ${CFLAGS} ${LINK} ${OBJS} -o editor

%.o: %.cc Makefile ${HEADERS}
	${CC} -c ${CFLAGS} $< -o $@
