.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=test
OBJS=socket.o rio.o tcp_connection.o poll_poller.o main_server.o
STARD=-std=c++0x
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.cc
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)
clean:
	rm -f *.o $(BIN)
