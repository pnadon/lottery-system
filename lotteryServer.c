/*
 * lotteryServer.c
 *
 * Philippe Nadon
 * Created on March 30, 2019
 *
 * Runs a server which handles requests to generate a random collection of lottery numbers.
 * The requests are sent from a client, which is then sent the generated numbers.
 */
#include "lotteryServer.h"

int main( int argc, char* argv[]) {
    int server_sockfd, client_sockfd;
    int server_len;
    unsigned int client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    int portAddress;
    if( argc < 2) {
        portAddress = 9734;
    } else {
        portAddress = atoi( argv[1]);
    }

    server_sockfd = socket( AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl( INADDR_ANY);
    server_address.sin_port = htons( portAddress);
    server_len = sizeof( server_address);
    bind( server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen( server_sockfd, 5);

    signal( SIGCHLD, SIG_IGN);

    while( TRUE) {
        printf("server waiting\n");

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,
                               (struct sockaddr *)&client_address, &client_len);

        if(fork() == 0) {
            while( handleClient( client_sockfd));
            close(client_sockfd);
            exit( EXIT_SUCCESS);
        }
        else {
            close(client_sockfd);
        }
    }
}

/*
 * Reads the clientPacket packet from the client specified by sockfd.
 * If CLOSE_SIGNAL is received, it returns CLOSE_SIGNAL to close the socket and kill the child process.
 * Otherwise, it generates random lottery numbers, and then sends them to the client.
 */
int handleClient( int client_sockfd) {
    clientPacket packet;
    read( client_sockfd, &packet, sizeof( packet));
    packet.numCount = ntohs( packet.numCount);
    packet.numMax = ntohs( packet.numMax);
    printf( "Received packet {%d, %d} from client\n", packet.numCount, packet.numMax);

    if( packet.numCount == CLOSE_SIGNAL) {
        printf("Received signal from child to terminate socket.\n");
        return CLOSE_SOCKET;
    }
    int response[ packet.numCount];
    generateLotteryNumbers( packet, response);
    printSendResponse( packet.numCount, response);
    sendResponse( client_sockfd, packet.numCount, response);
    return CONTINUE;
}

/*
 * Generates lottery numbers specified by clientPacket packet, and stores them in response.
 * The number of lottery numbers generated is specified by packet.numCount.
 * The maximum value of the lottery numbers is specified by packet.numMax.
 * The minimum value is 1.
 * The lottery numbers must be unique, and in order of ascending value.
 */
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

/*
 * Sends back the generated lottery numbers in response, to the client specified by sockfd.
 * numCount: The number of lottery numbers to send back.
 */
void sendResponse( int sockfd, int numCount, int response[]) {
    for( int i = 0; i < numCount; i++) {
        response[i] = htons( response[i]);
        write(sockfd, &response[i], sizeof( int));
    }
}

/*
 * Prints a message specifying the numbers in response being sent to the client.
 * numCount: The number of lottery numbers to send back.
 */
void printSendResponse( int numCount, int response[]) {
    printf("Sending:\n|");
    for( int i = 0; i < numCount; i++) {
        printf("%d ", response[i]);
    }
    printf("|\n");
}