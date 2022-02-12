#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	int num;
	char res1[1024];
	char res2[1024];
	char res3[1024];	

    	printf("Enter the number:- ");
    	scanf("%d",&num);

	send(sock , &num , sizeof(int) , 0 );
	printf("Number Sent to sever\n");

	valread = read( sock , &res1, sizeof(res1));
	valread = read( sock , &res2, sizeof(res2));
	valread = read( sock , &res3, sizeof(res3));

	printf("Result received from server :\n\n");

	printf("%s\n",res1);
	printf("%s\n",res2);
	printf("%s\n",res3);

	return 0;
}