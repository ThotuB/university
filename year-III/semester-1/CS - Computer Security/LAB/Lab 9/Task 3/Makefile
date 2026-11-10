.PHONY: all run clean

all: env

env: env.c
	gcc env.c -o env

run: env
	./env > out_null.txt
	./env -e > out_env.txt
	-diff out_null.txt out_env.txt

clean:
	rm -f env
