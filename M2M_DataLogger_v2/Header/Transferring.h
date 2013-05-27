#ifndef TRANSFERING_H_
#define TRANSFERING_H_

#include "Log.h"
#include "Main.h"

#define MSG_DELIMITER "/"
#define HEADER_SIZE 54

typedef struct {
	int msgType;
	int data_len;
	int msg_num;
	int msg_len;
	char header_msg[HEADER_SIZE+1];
}header_info;


static __inline int getMSGLength(char *msg)
{
	return strlen(msg);
}

static __inline int getTotalDataLength(char *msg)
{
	return getMSGLength(msg) + 54 + 1;
}


int transferData(int sock);
int checkConnection();
int tcpConnection(int *sock);
void makeHeaderInfo(header_info *headerData);
void *thread_transferring(void * arg);

#endif /* TRANSFERING_H_ */
