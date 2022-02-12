#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

struct cal {
        int a, b;
        char op;
}c;

int main(int argc, char const *argv[])
{
        int sock = 0, valread;
        struct sockaddr_in serv_addr;

        int a,b;
        char ch;
        printf("Enter two Numbers: ");
        scanf("%d %d",&a,&b);
        printf("Enter the operator: ");
        scanf(" %c",&ch);
        c.a = a;
        c.b = b;
        c.op = ch;

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
        send(sock , &c , sizeof(struct cal) , 0 );
        float result = 0;
        valread = read( sock , &result, 4);
        printf("Result: %f\n", result);
        return 0;
}