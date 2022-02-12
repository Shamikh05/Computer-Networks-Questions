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
	
	int len, n;char s[200];int count=0,i;
       
	

	len = sizeof(cliaddr); //len is value/resuslt

	n = recvfrom(sockfd, s, 200*sizeof(char),
				0, ( struct sockaddr *) &cliaddr,
				&len);
	
	for(i=0;s[i]!='\0';i++)
	{
	  if((s[i]==' ') && (s[i+1]!=' '))
	   count++;
	}

	sendto(sockfd, &count, sizeof(int),
		0, (const struct sockaddr *) &cliaddr,
			len);
	printf("\nCount of number of words in the given sentence has been sent.\n");
	
	return 0;
}