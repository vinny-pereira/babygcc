CC = gcc
CFLAGS = -Wall -g
TARGET = bin/babygcc
SOURCES = src/main.c src/lexer.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
