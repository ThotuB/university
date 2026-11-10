.PHONY: all run clean

all: catall

catall: catall.c
	gcc catall.c -o catall
	sudo chown root catall
	sudo chmod 4755 catall

run: catall
	./catall "../important_file.txt; echo REDACTED > ../important_file.txt"

clean:
	rm -f catall
