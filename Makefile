CC = gcc
EXE = hash
CFLAGS = -Wall -DDEBUG

$(EXE): main.o hash_str.o hash_int.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c hash_str.h
hash_str.o: hash_str.c hash_str.h list.h debug.h
hash_int.o: hash_int.c hash_int.h list.h debug.h

clean:
	rm -f *.o $(EXE)
