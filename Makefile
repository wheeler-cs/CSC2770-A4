CC=g++
CFLAGS=-Wall -pedantic -c

SRC_DIR=src
BUILD_DIR=build
OUT_EXE=server


# Build targets
all: $(BUILD_DIR)/main.o $(BUILD_DIR)/server.o
	$(CC) -lastyle $^ -o $(BUILD_DIR)/$(OUT_EXE) ./lib/libastyle-2.06d.so

# main.o
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/server.hpp
	$(CC) $(CFLAGS) $< -o $@

# server.o
$(BUILD_DIR)/server.o: $(SRC_DIR)/server.cpp $(SRC_DIR)/server.hpp
	$(CC) $(CFLAGS) $< -o $@


# Utility targets
.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/$(OUT_EXE)

.PHONY: run
run:
	LD_LIBRARY_PATH=./lib
	./$(BUILD_DIR)/$(OUT_EXE)
