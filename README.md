# lottery-system
A simulation of a lottery system using sockets.

The code has two parts:

1. A server which handles requests to generate a random collection of lottery numbers. The requests are sent from a client, which is then sent the generated numbers.
2. A client which handles a user's requests to generate random lottery numbers. The random lottery numbers are then sent to the server, which returns the numbers. The numbers are then displayed.
