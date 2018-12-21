CC=gcc
CFLAGS=-I.
DEPS = hello.h
OBJ = hello.o

%.o: %.c $(DEPS)
	    $(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	    gcc -o $@ $^ $(CFLAGS)


