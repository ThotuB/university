.PHONY: all run clean

all: printenv

printenv: printenv.c
	gcc printenv.c -o printenv

run: printenv
	./printenv -c > out_c.txt
	./printenv -p > out_p.txt
	-diff out_c.txt out_p.txt

clean:
	rm -f printenv
