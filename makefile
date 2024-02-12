CC = gcc
CFLAGS = -Imyheaders -Iexternal/src/include 
LDLIBS = -Lexternal/src/lib 
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_ttf 

SRC_DIR = src
BUILD_DIR = build

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(SRC_DIR)/main.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/tree.c $(SRC_DIR)/mapper.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

