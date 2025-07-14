CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = src/main.c
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
