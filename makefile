CC = gcc
CFLAGS = -Iinclude -Iexternal/src/include 
LDLIBS = -Lexternal/src/lib -lSDL2main -lSDL2 -lSDL2_ttf -mwindows

SRC_DIR = src
BUILD_DIR = build

all: $(BUILD_DIR)/my_parser

$(BUILD_DIR)/my_parser: $(SRC_DIR)/lexer.c $(SRC_DIR)/main.c $(SRC_DIR)/mapper.c $(SRC_DIR)/parser.c $(SRC_DIR)/tree.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

