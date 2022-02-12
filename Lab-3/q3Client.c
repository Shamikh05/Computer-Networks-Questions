// Client side implementation of UDP client-server model
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
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;char s[200];int i;int count=0;

	printf("Enter a sentence:- ");
	scanf("%[^\n]s", s);
	
	sendto(sockfd, s, 200*sizeof(char),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	
	len = sizeof(servaddr);
	n = recvfrom(sockfd, &count,sizeof(int),
				0, (struct sockaddr *) &servaddr,
				&len);
	
	printf("No of words in the given sentence : %d\n", count+1);

	close(sockfd);
	return 0;
}