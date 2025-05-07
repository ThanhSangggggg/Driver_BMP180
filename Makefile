CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -lwiringPi

SRC = max7219.c example.c
OBJ = $(SRC:.c=.o)

LIB = libmax7219.so
TARGET = example_demo

all: $(LIB) $(TARGET)

$(LIB): max7219.o
	$(CC) -shared -o $(LIB) max7219.o $(LDFLAGS)

$(TARGET): example.o
	$(CC) $(CFLAGS) -o $(TARGET) example.o -L. -lmax7219 $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB) $(TARGET) example.o

install:
	mv $(LIB) /usr/local/lib/
	mv max7219.h /usr/local/include/
	ldconfig

uninstall:
	rm -f /usr/local/lib/$(LIB)
	rm -f /usr/local/include/max7219.h
	ldconfig
