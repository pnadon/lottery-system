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

/*
 * Reads the clientPacket packet from the client specified by sockfd.
 * If CLOSE_SIGNAL is received, it returns CLOSE_SIGNAL to close the socket and kill the child process.
 * Otherwise, it generates random lottery numbers, and then sends them to the client.
 */
int handleClient( int client_sockfd);

/*
 * Generates lottery numbers specified by clientPacket packet, and stores them in response.
 * The number of lottery numbers generated is specified by packet.numCount.
 * The maximum value of the lottery numbers is specified by packet.numMax.
 * The minimum value is 1.
 * The lottery numbers must be unique, and in order of ascending value.
 */
void generateLotteryNumbers( clientPacket packet, int response[]);

/*
 * Sends back the generated lottery numbers in response, to the client specified by sockfd.
 * numCount: The number of lottery numbers to send back.
 */
void sendResponse( int sockfd, int numCount, int response[]);

/*
 * Prints a message specifying the numbers in response being sent to the client.
 * numCount: The number of lottery numbers to send back.
 */
void printSendResponse( int numCount, int response[]);
#endif //LOTTERYSYSTEM_LOTTERYSERVER_H
