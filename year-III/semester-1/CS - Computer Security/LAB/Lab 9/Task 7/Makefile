LIB = lib/libsleepy.so.1.0.1

.PHONY: all run clean

all: $(LIB) prog

sleepy.o: sleepy.c
	gcc -fPIC -g -c sleepy.c

$(LIB): sleepy.o
	mkdir -p lib
	gcc -shared -o $(LIB) sleepy.o -lc

prog: prog.c
	gcc prog.c -o prog

run: all
	LD_PRELOAD=./$(LIB) ./prog

clean:
	rm -f prog sleepy.o
