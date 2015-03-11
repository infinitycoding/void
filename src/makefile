SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = g++
CFLAGS = -Iinclude
BIN = ../void

$(BIN): $(OBJS)
	$(CC) -o $@ $^

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm $(OBJS)
	rm $(BIN)

