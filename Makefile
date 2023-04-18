CC=g++
CFLAGS=-Wall -pedantic -c

SRC_DIR=src
BUILD_DIR=build
OUT_EXE=server


all: $(BUILD_DIR)/main.o $(BUILD_DIR)/server.o
	$(CC) $^ -o $(BUILD_DIR)/$(OUT_EXE)


$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/server.hpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/server.o: $(SRC_DIR)/server.cpp $(SRC_DIR)/server.hpp
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/$(OUT_EXE)

.PHONY: run
run:
	./$(BUILD_DIR)/$(OUT_EXE)
