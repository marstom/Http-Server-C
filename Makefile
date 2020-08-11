CFLAGS=-I. -g -Wall -Wextra
PRPD_CFLAGS=-o3 -Wall -Wextra
OUT=marstom_server
LIBS=
CC=gcc

OBJ=server.o request_parser/request_parser.o utils/file_checker.o utils/log.o


debug: ${OBJ}
	${CC} ${OBJ} ${CFLAGS} -o ${OUT} ${LIBS}

production: ${OBJ}
	${CC} ${OBJ} ${PRPD_CFLAGS} -o ${OUT} ${LIBS}

test: ${OBJ}
	${CC} ${OBJ} ${CFLAGS} -o ${OUT} ${LIBS} && ./${OUT} && rm ./${OUT}

valgrind: ${OBJ}
	${CC} ${OBJ} ${CFLAGS} -o ${OUT} ${LIBS} && valgrind ./${OUT} && rm ./${OUT}


cleano:
	find . -type f -name '*.o' -delete
clean:
	rm ${OUT}
	find . -type f -name '*.o' -delete
