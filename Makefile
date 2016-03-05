CFLAGS += -Wall -pedantic -std=c11

all:
	cc *.c $(CFLAGS) `pkg-config --cflags --libs x11` -o y4m
clean:
	rm y4m
