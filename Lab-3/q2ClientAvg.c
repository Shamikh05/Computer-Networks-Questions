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
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;
	float result;
    int arr[5];
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

    printf("Enter Array Elements:-\n");
    for(int i=0;i<5;i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr[i]);
    }
	
	sendto(sockfd, arr, 5*sizeof(int),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));

    len = sizeof(servaddr);
	n = recvfrom(sockfd, &result,sizeof(float),
				0, (struct sockaddr *) &servaddr,
				&len);

	printf("Average : %f\n", result);

	close(sockfd);
	return 0;
}