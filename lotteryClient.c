/*
 * lotteryClient.c
 *
 * Philippe Nadon
 * Created on March 30, 2019
 *
 * Runs a client which handles a user's requests to generate random lottery numbers.
 * The random lottery numbers are then sent to the server, which returns the numbers.
 * The numbers are then displayed.
 */
#include "lotteryClient.h"

int main( int argc, char* argv[]) {
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char* ipAddress;
    int portAddress;
    if( argc < 3) {
        ipAddress = "127.0.0.1";
        portAddress = 9734;
    } else {
        ipAddress = argv[1];
        portAddress = atoi( argv[2]);
    }

    sockfd = socket( AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr( ipAddress);
    address.sin_port = htons( portAddress);
    len = sizeof( address);

    result = connect( sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        fprintf( stderr, "Failed to connect to server %s:%d : %s\n", ipAddress, portAddress, strerror(errno));
        exit( EXIT_FAILURE);
    }

    client( sockfd);
    exit( EXIT_SUCCESS);
}

void client( int sockfd) {
    int numCount;
    int numMax;

    while(1) {
        numCount = promptUser( NUMCOUNT_PROMPT);
        numMax = promptUser( NUMMAX_PROMPT);
        if( numCount == EOF || numMax == EOF) {
            printf("Recieved EOF, bye!\n");
            sendToServer( sockfd, CLOSE_SIGNAL, CLOSE_SIGNAL);
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
