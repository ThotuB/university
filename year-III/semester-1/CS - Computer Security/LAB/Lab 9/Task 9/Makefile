.PHONY: all run clean

all: cap_leak

cap_leak: cap_leak.c
	gcc cap_leak.c -o cap_leak
	sudo chown root cap_leak
	sudo chmod 4755 cap_leak

run: cap_leak
	./cap_leak

clean:
	rm -f cap_leak
