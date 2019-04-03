//
// Created by phil on 3/30/19.
//

#ifndef LOTTERYSYSTEM_LOTTERYCLIENT_H
#define LOTTERYSYSTEM_LOTTERYCLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define NUMCOUNT_PROMPT "Please enter how many lottery numbers you want:"
#define NUMMAX_PROMPT "Please enter the maximum value of the lottery numbers:"
#define CLOSE_SOCKET 0
#define CONTINUE 1
#define CLOSE_SIGNAL 0

/*
 * The clientPacket contains the two numbers sent to the server.
 * numCount: how many lottery numbers to generate
 * numMax: the maximum value of the lottery numbers
 */
typedef struct clientPacket {
    int numCount;
    int numMax;
} clientPacket;

void client( int sockfd);

int promptUser( char* msg, int sockfd);

void sendToServer( int sockfd, int numCount, int numMax);

void printServerResponse( int sockfd, int numCount);
#endif //LOTTERYSYSTEM_LOTTERYCLIENT_H
