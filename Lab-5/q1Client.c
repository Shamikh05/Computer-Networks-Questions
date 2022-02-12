#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
        char protocol_choice[4];
        short port;
        char qotds[5][100] = {
                "Simplicity is the ultimate sophistication",
                "It hurt because it mattered",
                "When words fail, music speaks",
                "Die with memories, not dreams",
                "Every moment's a fresh beginning"
        };

        printf("Enter the protocol of the server (udp/tcp): ");
        scanf("%s", protocol_choice);

        printf("Enter the server port: ");
        scanf("%hd", &port);

        if(strcmp(protocol_choice,"udp") == 0) {
                int sock;
                char* request = "qotd";
                struct sockaddr_in servaddr;
                char buffer[100];

                if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
                        perror("socket creation failed");
                        exit(EXIT_FAILURE);
                }

                memset(&servaddr, 0, sizeof(servaddr));

                //setting server info
                servaddr.sin_family = AF_INET;
                servaddr.sin_addr.s_addr = INADDR_ANY;
                servaddr.sin_port = htons(port);

                sendto(sock, request, strlen(request),
                        0, (const struct sockaddr *) &servaddr,
                        sizeof(servaddr));

                int n, len;
                len = sizeof(servaddr);
                n = recvfrom(sock, buffer, 100,
                        0, ( struct sockaddr *) &servaddr,
                        &len);
                buffer[n] = '\0';
                printf("%s\n",buffer);
                close(sock);

        }
        else if(strcmp(protocol_choice,"tcp") == 0) {
                int sock;
                char* request = "qotd";
                struct sockaddr_in servaddr;
                char buffer[100];

                if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
                        perror("socket creation failed");
                        exit(EXIT_FAILURE);
                }

                memset(&servaddr, 0, sizeof(servaddr));

                //setting server info
                servaddr.sin_family = AF_INET;
                servaddr.sin_addr.s_addr = INADDR_ANY;
                servaddr.sin_port = htons(port);

                if (connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
                {
                        printf("\nConnection Failed \n");
                        exit(EXIT_FAILURE);
                }

                send(sock , request , strlen(request) , 0 );

                int n, len;
                len = sizeof(servaddr);
                n = read( sock , buffer, 100);
                buffer[n] = '\0';
                printf("%s\n",buffer);
                close(sock);

        }
        else {
                printf("Protocol not supported\n");
                exit(EXIT_FAILURE);
        }
}