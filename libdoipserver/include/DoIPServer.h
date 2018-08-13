#ifndef DOIPSERVER_H
#define DOIPSERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstddef>

#include "DoIPGenericHeaderHandler.h"
#include "RoutingActivationHandler.h"
#include "DiagnosticMessageHandler.h"

const int _ServerPort = 13400;
const int _MaxDataSize = 64;

typedef void (*DiagnosticCallback)(unsigned char*, int);

class DoIPServer {
    public:
	DoIPServer(DiagnosticCallback diag_callback): diag_callback{diag_callback} { };
	void receiveFromApplication(unsigned char* value, int length);
	const DiagnosticCallback diag_callback;

        unsigned char data[_MaxDataSize];
        int sockfd_receiver, sockfd_sender;
        struct sockaddr_in serverAdress;
	unsigned char* sourceAddress;
	
        void setupSocket();
        void receiveMessage();
        void sendMessage(unsigned char* message, int messageLenght);
        void closeSocket();
};


#endif /* DOIPSERVER_H */

