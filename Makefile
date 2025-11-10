# Makefile for BENSCHILLIBOWL

CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -std=c11 -pthread
LDFLAGS := -pthread

TARGET  := benschillibowl
SRCS    := main.c BENSCHILLIBOWL.c
OBJS    := $(SRCS:.c=.o)
DEPS    := BENSCHILLIBOWL.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
