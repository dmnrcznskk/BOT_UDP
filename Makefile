
CC = gcc
CFLAGS = -std=c99 -g -Iinclude
SRC = main.c src/thermometer.c src/net.c
OUT = BotUDP 

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUT)
