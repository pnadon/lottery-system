//
// Created by phil on 3/30/19.
//

#ifndef LOTTERYSYSTEM_LOTTERYSERVER_H
#define LOTTERYSYSTEM_LOTTERYSERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define CLOSE_SOCKET 0
#define CONTINUE 1
#define CLOSE_SIGNAL 0

/*
 * The clientPacket contains the two numbers received from the client.
 * numCount: how many lottery numbers to generate
 * numMax: the maximum value of the lottery numbers
 */
typedef struct clientPacket {
    int numCount;
    int numMax;
} clientPacket;

int handleClient( int client_sockfd);

void generateLotteryNumbers( clientPacket packet, int response[]);

void sendResponse( int sockfd, int numCount, int response[]);

void printSendResponse( int numCount, int response[]);
#endif //LOTTERYSYSTEM_LOTTERYSERVER_H
