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

/*
 * Prompts the user the number of lottery numbers, and the max value the lottery numbers can have.
 * Afterwards, it sends them to the server specified by sockfd to be processed.
 * Finally, it takes the lottery numbers received from the server and prints them.
 */
void client( int sockfd);

/*
 * Prints the message specified in msg, and returns a correctly inputted number.
 * Loops if the number is invalid, or returns EOF if the user sends the EOF signal.
 */
int promptUser( char* msg, int sockfd);

/*
 * Sends a clientPacket packet to the server specified by sockfd.
 * The packet contains numCount, and numMax
 */
void sendToServer( int sockfd, int numCount, int numMax);

/*
 * Prints the numbers received from the server specified by sockfd.
 * The numbers represent randomly generated lottery numbers.
 * numCount represents how many numbers to print.
 */
void printServerResponse( int sockfd, int numCount);
#endif //LOTTERYSYSTEM_LOTTERYCLIENT_H
