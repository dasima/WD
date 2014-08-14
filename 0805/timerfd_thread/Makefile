.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=server
OBJS=timer.o thread.o timer_thread.o main_timer_thread.o
OTHER=-std=c++0x
LINKS=-lecho -lpthread
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKS)
%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(OTHER)
clean:
	rm -f *.o $(BIN)
