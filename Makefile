CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first.exe

first.o: scenarios/first.cpp 
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp 
	$(CC) $(CFLAGS) -c scenarios/second.cpp

first.exe: first.o link.o node.o
	$(CC) $(CFLAGS) -o first.exe first.o link.o node.o

second.exe: second.o link.o node.o
	$(CC) $(CFLAGS) -o second.exe second.o link.o node.o

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c link.cpp

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp

clean:
	rm -f *.o first second