CC=clang
CFLAGS=-g

simple_server: simple_mthread_server.o
	$(CC) $(CFLAGS) -o $@.out $^


clean:
	rm -rf *.out *.o