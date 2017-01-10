CFLAGS = -g -Wall -I./

ifdef debug
CFLAGS += -DDEBUG
endif

all: clean run

run: main.exe
	@./main.exe

main.exe: main.o
	$(CC) $(CFLAGS) -o $@ main.o

clean:
	rm -rf *.o *.exe
