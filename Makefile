CC = gcc
EXE = hash
CFLAGS = -Wall -DDEBUG
LDFLAGS = -lm

$(EXE): main.o hash.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o tags $(EXE)
