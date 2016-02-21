all:
	CFLAGS='-Wall -pedantic' cc *.c -g `pkg-config --cflags --libs x11` -o y4m
clean:
	rm y4m
