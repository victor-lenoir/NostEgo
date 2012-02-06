CFLAGS=-W -Wall -Wextra -Werror -Wfloat-equal -Wshadow -Wpointer-arith \
-Wcast-qual -Wcast-align -Wmissing-declarations -Wunused -Winline -pedantic \
-Wuninitialized -Winit-self
IFLAGS=-I src/ -I /lrde/beyrouth/lrde-2013/lenoir
LINK=-L /lrde/beyrouth/lrde-2013/lenoir/NostEgo/game -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
CC=g++

all: Makefile.inc nostego nostego_server nostego_debug nostego_server_debug # Build all targets

clean: # Clean the repository
	rm -f `find . -name '*.o'`
	rm -f `find . -name '*~'`
	rm -f `find . -name '*#'`
	rm -f Makefile.inc
	rm -f nostego nostego_server nostego_debug nostego_server_debug

Makefile.inc: # Build the included makefile
	./configure

include Makefile.inc

nostego_debug: ${OBJS} src/main.o # Build nostego client version debug
	${CC} ${CFLAGS} -g -ggdb ${LINK} $^ -o nostego_debug

nostego_server: ${OBJS} src/server/main.o # Build nostego server
	${CC} ${CFLAGS} ${LINK} $^ -o nostego_server

nostego_server_debug: ${OBJS} src/server/main.o # Build nostego server version debug
	${CC} ${CFLAGS} -g -ggdb ${LINK} $^ -o nostego_server_debug

nostego: ${OBJS} src/main.o # Build nostego client
	${CC} ${CFLAGS} ${LINK} $^ -o nostego

exec: nostego # Exec nost ego client
	LD_LIBRARY_PATH=. ./nostego

debug: nostego_debug # Valgrind nostego server
	LD_LIBRARY_PATH=. valgrind ./nostego_debug

exec_server: nostego_server # Exec nostego server
	LD_LIBRARY_PATH=. ./nostego_server

server_debug: nostego_server_debug # Valgrind nostego server
	LD_LIBRARY_PATH=. valgrind ./nostego_server_debug
