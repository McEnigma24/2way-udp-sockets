#pragma once
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <chrono>

using namespace std;

#define log(x) cout << #x << " = " << x << endl;

#define MAXLINE     (5000)

class Udp_socket
{
    protected:
    int sockfd;
    socklen_t rec_socket_len;
    sockaddr_in servaddr, cliaddr;
    struct timeval timeout;

    Udp_socket(const string& ip, const uint32_t port)
        :sockfd(-1), rec_socket_len(sizeof(cliaddr))
    {
        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        if((sockfd = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
        servaddr.sin_port = htons(port);
    }

    ~Udp_socket()
    {
        close(sockfd);
    }
};
