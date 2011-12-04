all: main

main: main.o cclient.o cserver.o
	g++ -o $@ $^ -lpthread

%.o:%.c
	g++ -c $<

clean:
	rm *.o -rf
	rm main -rf

	
