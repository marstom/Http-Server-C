CC=clang
CFLAGS=-g -Wall
LIBS=
OBJS_CLIENT=obj/tcpclient.o obj/common.o
OBJS_SERVER=obj/tcpserver.o obj/common.o

BASE_OBJ=obj

clean:
	rm -rf *.o *.out *.s tcpclient.out
	rm -rf obj/*.o

tcpclient: $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o tcpclient.out

tcpserver: $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o tcpserver.out

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


install_dependencies:
	mkdir munit
	git clone https://github.com/nemequ/munit.git ./munit