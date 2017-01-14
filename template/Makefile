SRC    = main
INPUT  = input.txt
OUTPUT = output.txt
MOCHA  = ../../mocha
CFLAGS = -g -Wall -I./ -I$(MOCHA)
OBJS   = $(SRC).o $(MOCHA)/mocha.o

all: clean output

debug: clean
	$(CC) $(CFLAGS) -DDEBUG -c $(SRC).c
	$(CC) $(CFLAGS) -DDEBUG $(OBJS) -o $@.exe
	cat $(INPUT) | ./$@.exe

test: clean $(MOCHA)/mocha.o
	$(CC) $(CFLAGS) -DTEST -c $(SRC).c
	$(CC) $(CFLAGS) -DTEST $(OBJS) -o $@.exe
	./$@.exe

output: clean
	$(CC) $(CFLAGS) -c $(SRC).c
	$(CC) $(CFLAGS) $(OBJS) -o $(SRC).exe
	cat $(INPUT) | ./$(SRC).exe > $(OUTPUT)

clean:
	rm -rf *.o *.exe
