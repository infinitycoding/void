SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = g++
BIN = ../testproc

$(BIN): $(OBJS)
	$(CC) -o $@ $^

%.o : %.cpp
	$(CC) -c -o $@ $<

clean:
	rm $(OBJS)
	rm $(BIN)

