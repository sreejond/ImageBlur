CC=g++
CFLAGS=-std=c++11 -c -Wall `libpng-config --cflags` 

all: ImageBlur

ImageBlur: Tester.o ImageBlurUtil.o
	$(CC) Tester.o ImageBlurUtil.o -o ImageBlur `libpng-config --ldflags`

Tester.o: Tester.cpp
	$(CC) $(CFLAGS) Tester.cpp
	
ImageBlurUtil.o: ImageBlurUtil.cpp
	$(CC) $(CFLAGS) ImageBlurUtil.cpp

clean:
	rm -rf *.o ImageBlur
