CC=g++
CFLAGS=-g -Wall -pedantic


# Build targets
all: main.o server.o
	$(CC) $(CFLAGS) $^ libastyle-2.06d.so -o server -lastyle

main.o: main.cpp server.hpp
	$(CC) -c main.cpp -o main.o

server.o: server.cpp server.hpp
	$(CC) -c server.cpp -o server.o


# Utility targets
.PHONY: clean
clean:
	rm ./*.o
	rm ./server

.PHONY: run
run:
	./$(BUILD_DIR)/$(OUT_EXE)
