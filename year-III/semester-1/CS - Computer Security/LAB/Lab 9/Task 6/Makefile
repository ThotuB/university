.PHONY: all run clean

all: ls

ls: ls.c
	gcc ls.c -o ls

# put the current directory first in PATH so the fake ls shadows /bin/ls
run: ls
	PATH=.:$$PATH ls

clean:
	rm -f ls important_file.txt
