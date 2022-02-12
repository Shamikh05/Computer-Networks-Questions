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

int word_count(char s[MAXLINE])
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ' && s[i + 1] != ' ')
            count++;
    }
    return count + 1;
}

// Driver code
int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
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
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len;
    int sent[5];
    char input[5][MAXLINE];

    len = sizeof(cliaddr);

    recvfrom(sockfd, &input, sizeof(input),
             0, (struct sockaddr *)&cliaddr,
             &len);

    for (int i = 0; i < 5; i++)
    {
        sent[i] = word_count(input[i]);
    }
   
    int max_words = sent[0];
    for (int i = 0; i < 5; i++)
    {
        if (sent[i] > max_words)
            max_words = sent[i];
    }

    sendto(sockfd, &max_words, sizeof(max_words),
           0, (const struct sockaddr *)&cliaddr,
           len);

    printf("\nMaximum Word sent to client\n");

    return 0;
}