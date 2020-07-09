CC = gcc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = main

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)