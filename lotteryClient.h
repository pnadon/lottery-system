//
// Created by phil on 3/30/19.
//

#ifndef LOTTERYSYSTEM_LOTTERYCLIENT_H
#define LOTTERYSYSTEM_LOTTERYCLIENT_H
#define TRUE 1
#define FALSE 0

typedef struct clientPacket {
    int numCount;
    int numMax;
} clientPacket;

void client( int sockfd);
int promptUser( char* msg);
void sendToServer( int sockfd, int numCount, int numMax);
void printServerResponse( int sockfd, int numCount);
#endif //LOTTERYSYSTEM_LOTTERYCLIENT_H
