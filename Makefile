CFLAGS=-g -Wall -Wextra
PRPD_CFLAGS=-o3 -Wall -Wextra
OUT=marstom_server
LIBS=
SOURCES=server.c ./request_parser/request_parser.c ./utils/file_checker.c

CC=gcc

debug:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS}

production:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS}

test:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS} && ./${OUT} && rm ./${OUT}

valgrind:
	${CC} ${SOURCES} ${CFLAGS} -o ${OUT} ${LIBS} && valgrind ./${OUT} && rm ./${OUT}


clean:
	rm ${OUT}
