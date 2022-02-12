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

int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	

	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;
	int num,i;
	long long int result = 1;

	len = sizeof(cliaddr);

	n = recvfrom(sockfd, &num, sizeof(int),
				0, ( struct sockaddr *) &cliaddr,
				&len);
	
	printf("\nInteger value from client received !!\n");

	for(i=2;i<=num;i++) {
		result *= i;
	}

	sendto(sockfd, &result, sizeof(long long int),
		0, (const struct sockaddr *) &cliaddr,
			len);

	printf("\nFactorial value sent to client !!\n");
	
	return 0;
}