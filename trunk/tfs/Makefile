OBJS = write_sample_3500 read_sample_3500
all: $(OBJS)

CFLAGS= -g -I/home/linqing.zyd/tfs-bin/include -I/home/linqing.zyd/lib/include/tbnet -I/home/linqing.zyd/lib/include/tbsys
LIBS=-L/home/linqing.zyd/tfs-bin/lib -L/home/linqing.zyd/lib/lib -ltbsys -ltbnet -ltfsclient -lz


write_sample_3500: write_sample_3500.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
read_sample_3500: read_sample_3500.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf *.o $(OBJS)
