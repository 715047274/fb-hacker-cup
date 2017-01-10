CFLAGS = -g -Wall -I./ -I../../mocha

ifdef debug
CFLAGS += -DDEBUG
endif

ifdef test
CFLAGS += -DTEST
endif

all: clean run

run: main.exe
	@./main.exe

main.exe: main.o ../../mocha/mocha.o
	$(CC) $(CFLAGS) -o $@ main.o ../../mocha/mocha.o

clean:
	rm -rf *.o *.exe
