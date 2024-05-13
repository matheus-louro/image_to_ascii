SRC=ascii.c
BIN=ascii
CC=gcc
LIBS=-lm

all:
	$(CC) -o $(BIN) $(SRC) $(LIBS)

clean:
	$(RM) $(BIN) $(BIN).exe