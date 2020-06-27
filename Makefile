CFLAGS=-g -Wall -Wextra
OUT=marstom_server
LIBS=
SOURCES=server.c ./request_parser/request_parser.c ./utils/file_checker.c

CC=gcc

all:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS}

test:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS} && ./${OUT} && rm ./${OUT}

valgrind:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS} && valgrind ./${OUT} && rm ./${OUT}


clean:
	rm ${OUT}
