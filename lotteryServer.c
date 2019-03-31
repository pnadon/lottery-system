//
// Created by phil on 3/30/19.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "lotteryServer.h"

int main()
{
    int server_sockfd, client_sockfd;
    int server_len;
    unsigned int client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue, ignore child exit details and wait for clients.  */

    listen(server_sockfd, 5);

    signal(SIGCHLD, SIG_IGN);

    while( TRUE) {
        printf("server waiting\n");

/*  Accept connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,
                               (struct sockaddr *)&client_address, &client_len);

/*  Fork to create a process for this client and perform a test to see
    whether we're the parent or the child. */

        if(fork() == 0) {

/*  If we're the child, we can now read/write to the client on client_sockfd.
    The five second delay is just for this demonstration.  */

            handleClient( client_sockfd);
            exit( EXIT_SUCCESS);
        }

/*  Otherwise, we must be the parent and our work for this client is finished.  */

        else {
            close(client_sockfd);
        }
    }
}

void handleClient( int client_sockfd) {
    clientPacket packet;
    read(client_sockfd, &packet, sizeof( packet));
    printf("Received packet {%d, %d} from client\n", packet.numCount, packet.numMax);
    int response[ packet.numCount];
    generateLotteryNumbers( packet, response);
    printSendResponse( packet.numCount, response);
    sendResponse( client_sockfd, packet.numCount, response);
    close(client_sockfd);
}

void generateLotteryNumbers( clientPacket packet, int response[]) {
    int responseIndex = 0;
    srand(time(NULL));
    double randReal;

    double select = (double)packet.numCount;
    double remaining = (double)packet.numMax;
    for( int i = 1; i < (packet.numMax + 1); i++) {
        randReal = rand() / ((double) RAND_MAX + 1);
        if( randReal < ( (double)select / (double)remaining)) {
            response[ responseIndex] = i;
            responseIndex++;
            select = select - 1;
        }
        remaining = remaining - 1;
    }
}

void sendResponse( int sockfd, int numCount, int response[]) {
    for( int i = 0; i < numCount; i++) {
        write(sockfd, &response[i], sizeof( int));
    }
}

void printSendResponse( int numCount, int response[]) {
    printf("Sending:\n|");
    for( int i = 0; i < numCount; i++) {
        printf("%d ", response[i]);
    }
    printf("|\n");
}