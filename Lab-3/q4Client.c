// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

struct Data
{
	int id;
	char name[50];
};

// Driver code
int main()
{
	int sockfd;
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	int len = sizeof(servaddr);

	struct Data d;
	struct Data d2;

	printf("\nEnter name: ");
	scanf("%[^\n]", d.name);
	printf("\nEnter id: ");
	scanf("%d", &d.id);

	sendto(sockfd, &d, sizeof(d),
		   0, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));

	recvfrom(sockfd, &d2, sizeof(d2),
				 0, (struct sockaddr *)&servaddr,
				 &len);
	printf("\nid sent from server : %d\n", d2.id);
	printf("\nname sent from server : %s\n", d2.name);

	close(sockfd);
	return 0;
}