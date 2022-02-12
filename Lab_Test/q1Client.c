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
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;
	int num;
	long long int result;

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;

	printf("\nEnter any integer : ");
	scanf("%d",&num);
	
	sendto(sockfd, &num, sizeof(int),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	
	printf("\nInteger value sent to server !!\n");

		
	n = recvfrom(sockfd, &result,sizeof(long long int),
				0, (struct sockaddr *) &servaddr,
				&len);
	printf("\nResult from server received !!\n");

	printf("\nThe Factorial is %lld and my roll number is 1906428 !!\n", result);

	close(sockfd);
	return 0;
}