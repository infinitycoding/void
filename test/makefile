SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

C_SRCS = $(shell find `pwd` -name '*.cpp')
C_HDRS = $(shell find `pwd` -name '*.h')
STYLEFLAGS = --style=allman --indent-switches

CC = g++
BIN = ../testproc

$(BIN): $(OBJS)
	$(CC) -o $@ $^

%.o : %.cpp
	$(CC) -c -o $@ $<

style: $(C_SRCS) $(C_HDRS)
	astyle $(STYLEFLAGS) $^

clean:
	rm $(OBJS)
	rm $(BIN)

