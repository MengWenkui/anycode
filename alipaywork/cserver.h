#ifndef _SERVER_H
#define _SERVER_H

class CServer {	
private:
	int listenfd;
public:
	CServer(int port = SERV_PORT); // create socket and listen
	int accept();                  // accept a connection
	void process(int fd); 		   // process request
	~CServer();
};

#endif