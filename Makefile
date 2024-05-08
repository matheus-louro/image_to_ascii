SRC=main.c
BIN=main
CC=gcc
LIBS=-lm

all:
	$(CC) -o $(BIN) $(SRC) $(LIBS)

clean:
	$(RM) $(BIN) $(BIN).exe