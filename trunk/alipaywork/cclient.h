#ifndef _CLIENT_H
#define _CLIENT_H

class CClient {
private:
	int sockfd;
public:
	CClient();
	int connect(char *ip, int port);
	void request(); // send request
	~CClient();
};

#endif