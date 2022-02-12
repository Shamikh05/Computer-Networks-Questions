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
	char *hello1 = "1";
	char *hello2 = "2";
	struct sockaddr_in	 servaddr;

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
	
	int n, len;
	char inputa[MAXLINE], inputb[MAXLINE];
	int a,b;
	
	printf("\nEnter first number: ");
	scanf("%d", &a);	
	sprintf(inputa, "%d", a);
	
	sendto(sockfd, (const char *)inputa, strlen(inputa),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("value sent: %s\n", inputa);

	printf("\nEnter second number: ");
	scanf("%d", &b);	
	sprintf(inputb, "%d", b);

	sendto(sockfd, (const char *)inputb, strlen(inputb),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("value sent: %s\n", inputb);
		
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				0, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	printf("Sum sent from server : %s\n", buffer);

	close(sockfd);
	return 0;
}
