.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=main
OBJS=thread.o condition.o thread_pool.o pool_main.o
LINK=-lpthread
STAR=-std=c++0x
$(BIN):$(OBJS)
	$(CC) $(CFLAFS) $^ -o $@ $(LINK)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STAR)
clean:
	rm -f *.o $(BIN)
