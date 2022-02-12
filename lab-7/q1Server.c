#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    int a,i,r,sum=0;
    int check=1;

    char res1[1024];
    char res2[1024];
    char res3[1024];

    read(new_socket, &a, sizeof(a));
    printf("Number Received is %d\n",a);

    if(a%2==0) {
	strcpy(res1, "It is an even number!");
    }
    else {
	strcpy(res1, "It is an odd number!");
    }

    for(i=2;i<a;i++) {
	if(a%i==0) {
		check = 0;
		break;		
	}
    }

    if(check) {
	strcpy(res2, "It is a prime number!");
    }
    else {
	strcpy(res2, "It is not a prime number!");
    }

    int temp = a;

    while (a > 0)
    {
        r = a % 10;
        sum = sum + (r * r * r);
        a = a / 10;
    }
    if (temp == sum)
        strcpy(res3, "It is an armstrong number!");
    else
        strcpy(res3, "It is not an armstrong number!");


    send(new_socket, &res1, sizeof(res1), 0);
    send(new_socket, &res2, sizeof(res2), 0);
    send(new_socket, &res3, sizeof(res3), 0);

    printf("Result Sent\n");
    close(new_socket); // closes this particular connection
    close(server_fd); // server cannot accept any more connections
    return 0;
}