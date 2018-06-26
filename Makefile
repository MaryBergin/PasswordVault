CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g

test: src/main.c src/HashTableAPI.c src/PasswordVault.c
	$(CC) $(CFLAGS) src/main.c src/HashTableAPI.c src/PasswordVault.c -g -Iinclude -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

#add a second target to build a different program with the same library
prog: src/HashTableAPI.c src/PasswordVault.c
	$(CC) $(CFLAGS)  src/HashTableAPI.c src/PasswordVault.c -Iinclude -o bin/runMe

doxy: Doxyfile
		doxygen

clean:
		rm bin/*
