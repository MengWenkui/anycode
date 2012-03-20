OBJS=echoserver echoclient

all: $(OBJS)

CC=g++
CFLAGS=-g -I/home/linqing.zyd/lib/include/tbsys -I/home/linqing.zyd/lib/include/tbnet
LIBS=-L/home/linqing.zyd/lib/lib -ltbsys -ltbnet

echoserver: echo_server.o
	$(CC) -o $@ $^ $(LIBS)

echoclient: echo_client.o
	$(CC) -o $@ $^ $(LIBS)

echo_server.o: echo_server.cpp
	$(CC) -c $^ $(CFLAGS)

echo_client.o: echo_client.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm *.o $(OBJS) -rf
