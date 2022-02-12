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

        printf("Enter the protocol (udp/tcp): ");
        scanf("%s", protocol_choice);

        printf("Enter the port to bind to: ");
        scanf("%hd", &port);

        if(strcmp(protocol_choice,"udp") == 0) {
                int sock;
                char request[8];
                struct sockaddr_in servaddr, cliaddr;
                char* invalid_request = "Invalid Request";

                if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
                        perror("socket creation failed");
                        exit(EXIT_FAILURE);
                }

                memset(&servaddr, 0, sizeof(servaddr));
                memset(&cliaddr, 0, sizeof(cliaddr));

                //setting server info
                servaddr.sin_family = AF_INET;
                servaddr.sin_addr.s_addr = INADDR_ANY;
                servaddr.sin_port = htons(port);

                if ( bind(sock, (const struct sockaddr *)&servaddr,
                                sizeof(servaddr)) < 0 )
                {
                        perror("bind failed");
                        exit(EXIT_FAILURE);
                }

                while(1) {
                        int random_number;
                        random_number = rand() % 5;

                        int n, len;
                        len = sizeof(cliaddr);
                        n = recvfrom(sock, request, 8,
                                0, ( struct sockaddr *) &cliaddr,
                                &len);
                        request[n] = '\0';
                        if(strcmp(request,"qotd") == 0) {
                                sendto(sock, qotds[random_number], strlen(qotds[random_number]),
                                        0, (const struct sockaddr *) &cliaddr,
                                        sizeof(cliaddr));
                        } else {
                                sendto(sock, invalid_request, strlen(invalid_request),
                                        0, (const struct sockaddr *) &cliaddr,
                                        sizeof(cliaddr));
                        }
                }


        }
        else if(strcmp(protocol_choice,"tcp") == 0) {
                int sock;
                char request[8];
                struct sockaddr_in servaddr, cliaddr;
                char* invalid_request = "Invalid Request";

                if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
                        perror("socket creation failed");
                        exit(EXIT_FAILURE);
                }

                memset(&servaddr, 0, sizeof(servaddr));
                memset(&cliaddr, 0, sizeof(cliaddr));

                //setting server info
                servaddr.sin_family = AF_INET;
                servaddr.sin_addr.s_addr = INADDR_ANY;
                servaddr.sin_port = htons(port);

                if ( bind(sock, (const struct sockaddr *)&servaddr,
                                sizeof(servaddr)) < 0 )
                {
                        perror("bind failed");
                        exit(EXIT_FAILURE);
                }

                if (listen(sock, 3) < 0) {
                        perror("listen");
                        exit(EXIT_FAILURE);
                }

                while(1) {
                        int random_number, new_sock, len;
                        random_number = rand() % 5;
                        len = sizeof(cliaddr);

                        if ((new_sock = accept(sock, (struct sockaddr *)&cliaddr,
                             (socklen_t *)&len)) < 0)
                        {
                                perror("accept");
                                exit(EXIT_FAILURE);
                        }

                        int n;
                        n = read(new_sock, request, 8);
                        request[n] = '\0';
                        if(strcmp(request,"qotd") == 0) {
                                send(new_sock, qotds[random_number], strlen(qotds[random_number]), 0);
                        } else {
                                send(new_sock, invalid_request, strlen(invalid_request), 0);
                        }
                        close(new_sock);
                }

        }
        else {
                printf("Protocol not supported\n");
                exit(EXIT_FAILURE);
        }
}