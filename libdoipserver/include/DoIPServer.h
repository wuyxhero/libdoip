#ifndef DOIPSERVER_H
#define DOIPSERVER_H

#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include "DoIPGenericHeaderHandler.h"
#include "RoutingActivationHandler.h"
#include "VehicleIdentificationHandler.h"
#include "DoIPGenericHeaderHandler.h"
#include "RoutingActivationHandler.h"
#include "DiagnosticMessageHandler.h"

const int _ServerPort = 13400;
const int _MaxDataSize = 64;   

class DoIPServer {

public:
    DoIPServer() = default;
    DoIPServer(DiagnosticCallback diag_callback): diag_callback{diag_callback} { };
    void setCallback(DiagnosticCallback cb);              
    void setupSocket();
    void setupUdpSocket();
    int receiveMessage();
    int receiveUdpMessage();
    void receiveDiagnosticPayload(unsigned char* value, int length);
    void closeSocket();
    void closeUdpSocket();

    const unsigned char* getData();
    int getDataLength() const;

    void setEIDdefault();
    void setVIN(const char* VINString);
    void setLogicalAddress(const unsigned int inputLogAdd);
    void setEID(const unsigned long inputEID);
    void setGID(const unsigned long inputGID);
    void setFAR(const unsigned int inputFAR);


private:
    DiagnosticCallback diag_callback;
    unsigned char data[_MaxDataSize];
    int dataLength;
    int sockfd_receiver, sockfd_receiver_udp, sockfd_sender;
    struct sockaddr_in serverAddress, clientAddress;
    unsigned char* routedClientAddress;
    
    char VIN [18] = "00000000000000000"; //17 chars VIN + /0 char
    unsigned char LogicalAddress [2] = {0x00, 0x00};
    unsigned char EID [6];
    unsigned char GID [6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char FurtherActionReq = 0x00;

    int sendMessage(unsigned char* message, int messageLenght);
    int sendUdpMessage(unsigned char* message, int messageLength);
    void setMulticastGroup(const char* address);

        
    
};

#endif /* DOIPSERVER_H */