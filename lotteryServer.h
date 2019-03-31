//
// Created by phil on 3/30/19.
//

#ifndef LOTTERYSYSTEM_LOTTERYSERVER_H
#define LOTTERYSYSTEM_LOTTERYSERVER_H
#define TRUE 1
#define FALSE 0

typedef struct clientPacket {
    int numCount;
    int numMax;
} clientPacket;

void handleClient( int client_sockfd);
void generateLotteryNumbers( clientPacket packet, int response[]);
void sendResponse( int sockfd, int numCount, int response[]);
void printSendResponse( int numCount, int response[]);
#endif //LOTTERYSYSTEM_LOTTERYSERVER_H
