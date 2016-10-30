CC = gcc
EXE = hash
CFLAGS = -Wall -DDEBUG

$(EXE): main.o hash.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o tags $(EXE)
