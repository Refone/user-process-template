CC=gcc
CFLAGS=-I.
DEPS = hello.h
OBJ = hello.o
TCP_S_OBJ = tcp_server.o
TCP_C_OBJ = tcp_client.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

tcp_s: $(TCP_S_OBJ)
	gcc -o $@ $^ $(CFLAGS)

tcp_c: $(TCP_C_OBJ)
	gcc -o $@ $^ $(CFLAGS)

tcp:
	make tcp_s
	make tcp_c
