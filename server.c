#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h> // for getaddrinfo, inet_pton, etc.
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct addrinfo hints;
    struct addrinfo *serverinfo;
    int status;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    printf("the size of struct addrinfo is: %d bytes\n", sizeof(hints));

    status = getaddrinfo("www.google.com", "http", &hints, &serverinfo);
    if (status != 0)
    {
        printf("There was an error\n");
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerrorA(status));
    }
    else
    {
        printf("Check was successful\n");
        printf("ai_family: %d\n", serverinfo->ai_family);
    }

    struct sockaddr_in *storedIP = NULL;

    if (serverinfo->ai_family == AF_INET)
    {
        storedIP = (struct sockaddr_in *)serverinfo->ai_addr;
    }
    // struct socketaddr_in* storedIP;

    if (storedIP != NULL)
    {
        char ip4[INET_ADDRSTRLEN];

        printf("The IP address is %s\n", inet_ntop(AF_INET, &(storedIP->sin_addr), ip4, INET_ADDRSTRLEN));
    }

    freeaddrinfo(serverinfo);
}


// need to revise pointers, variables, data types and memory management