CC = gcc
CFLAGS = -Wall -O2 -I./lib
LDFLAGS = -lncurses
TARGET = doro

SRCS = src/main.c $(wildcard lib/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	sudo mkdir -p /usr/local/bin
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
