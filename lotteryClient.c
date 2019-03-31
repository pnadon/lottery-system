//
// Created by phil on 3/30/19.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "lotteryClient.h"

int main(int argc, char* argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char* ipAddress;
    int portAddress;
    if(argc < 3) {
        ipAddress = "127.0.0.1";
        portAddress = 9734;
    } else {
        ipAddress = argv[1];
        portAddress = atoi(argv[2]);
    }

/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddress);
    address.sin_port = htons(portAddress);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: lotteryClient");
        exit(1);
    }

/*  We can now read/write via sockfd.  */
    client( sockfd);
    exit(0);
}

void client( int sockfd) {
    int numCount;
    int numMax;
    char* msg1 = "Please enter how many lottery numbers you want:";
    char* msg2 = "Please enter the maximum value of the lottery numbers:";

    while(1) {
        numCount = promptUser( msg1);
        numMax = promptUser( msg2);
        if( numCount == EOF || numMax == EOF) {
            printf("Recieved EOF, bye!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        if( numMax > numCount) {
            sendToServer( sockfd, numCount, numMax);
            printServerResponse( sockfd, numCount);
        } else {
            perror("incorrect input. The second number must be greater than the first.\n");
        }
    }
}
int promptUser( char* msg) {
    int scanfRetVal = 0;
    int res = 0;
    int correctInput = FALSE;

    while( !correctInput) {
        printf("%s\n", msg);
        scanfRetVal = scanf("%d", &res);
        if( scanfRetVal == EOF) {
            return EOF;
        } else if( (scanfRetVal == 0) || (res < 1)) {
            printf("incorrect input. Please enter a positive integer\n");
        } else {
            correctInput = TRUE;
        }
    }
    return res;
}

void sendToServer( int sockfd, int numCount, int numMax) {
    clientPacket packet = {
            numCount,
            numMax
    };
    write(sockfd, &packet, sizeof( packet));
}

void printServerResponse( int sockfd, int numCount) {
    printf("Your lottery numbers:\n");
    int response;
    while ( numCount > 0) {
        read(sockfd, &response, sizeof(response));
        printf("%d\n", response);
        numCount--;
    }
    printf("----------------\n");
    printf("Done!\n\n");
}
