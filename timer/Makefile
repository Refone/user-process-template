CC=gcc
CFLAGS=-I.
#DEPS = hello.h
OBJ = timer.o

%.o: %.c $(DEPS)
	    $(CC) -c -o $@ $< $(CFLAGS)

timer: $(OBJ)
	    gcc -o $@ $^ $(CFLAGS)


