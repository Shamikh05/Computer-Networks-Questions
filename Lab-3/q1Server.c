// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;
	int a,b,result;

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, &a, sizeof(int),
				0, ( struct sockaddr *) &cliaddr,
				&len);
	
	n = recvfrom(sockfd, &b, sizeof(int),
				0, ( struct sockaddr *) &cliaddr,
				&len);

	result = a+b;

	// buffer[n] = '\0';
	// printf("Client : %s\n", buffer);

	sendto(sockfd, &result, sizeof(int),
		0, (const struct sockaddr *) &cliaddr,
			len);
	printf("Sum of the two numbers sent.\n");
	
	return 0;
}