CC=g++
CFLAGS=-Wall -pedantic -c

SRC_DIR=src
BUILD_DIR=build
OUT_EXE=server


all: $(BUILD_DIR)/main.o
	$(CC) $^ -o $(BUILD_DIR)/$(OUT_EXE)


$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/*.pch
	rm $(BUILD_DIR)/$(OUT_EXE)

.PHONY: run
run:
	./$(BUILD_DIR)/$(OUT_EXE)
