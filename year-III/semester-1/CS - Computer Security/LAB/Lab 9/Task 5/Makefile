.PHONY: all run clean

all: env

env: env.c
	gcc env.c -o env
	sudo chown root env
	sudo chmod 4755 env

run: env
	export LD_LIBRARY_PATH=/usr/local/lib MY_VAR=sleepy; \
	env > out_env.txt; \
	./env > out_cenv.txt
	-diff out_env.txt out_cenv.txt

clean:
	rm -f env
