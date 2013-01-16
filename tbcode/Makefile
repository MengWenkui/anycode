OBJS = write_sample read_sample rcclient_sample meta_client_sample rc_client_file_test write_sample_large write_sample_3500 read_sample_3500
all: $(OBJS)

CFLAGS= -g -I/home/linqing.zyd/tfs-bin/include -I/home/linqing.zyd/lib/include/tbnet -I/home/linqing.zyd/lib/include/tbsys
LIBS=-L/home/linqing.zyd/tfs-bin/lib -L/home/linqing.zyd/lib/lib -ltbsys -ltbnet -ltfsclient -lz


write_sample: write_sample.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
write_sample_large: write_sample_large.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
read_sample: read_sample.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
rcclient_sample: rcclient_sample.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
meta_client_sample: meta_client_sample.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
rc_client_file_test: rc_client_file_test.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
write_sample_3500: write_sample_3500.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
read_sample_3500: read_sample_3500.cpp
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf *.o $(OBJS)
