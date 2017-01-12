SRC    = main
INPUT  = input.txt
OUTPUT = output.txt
CFLAGS = -g -Wall -I./ -I../../mocha/
OBJS   = $(SRC).o ../../mocha/mocha.o

all: clean output

debug: clean
	$(CC) $(CFLAGS) -DDEBUG -c $(SRC).c
	$(CC) $(CFLAGS) -DDEBUG $(OBJS) -o $@.exe
	cat $(INPUT) | ./$@.exe

test: clean ../../mocha/mocha.o
	$(CC) $(CFLAGS) -DTEST -c $(SRC).c
	$(CC) $(CFLAGS) -DTEST $(OBJS) -o $@.exe
	./$@.exe

output: clean
	$(CC) $(CFLAGS) -c $(SRC).c
	$(CC) $(CFLAGS) $(OBJS) -o $(SRC).exe
	cat $(INPUT) | ./$(SRC).exe > $(OUTPUT)

clean:
	rm -rf *.o *.exe
