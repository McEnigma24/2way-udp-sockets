#include "udp_client.h"
#include "udp_server.h"


Udp_server::Udp_server(const string& ip, const uint32_t port)
    :Udp_socket(ip, port)
{
    if(::bind(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Udp_server::wait_for_init_msg_than_resp(Udp_client* sender)
{
    vector<uint8_t> buffer;

    receive(buffer);
    sender->send(buffer);

    cout << "INT - completed\n";
}

void Udp_server::set_timeout(int seconds, int microseconds)
{
    timeout.tv_sec = seconds;
    timeout.tv_usec = microseconds;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
}

int Udp_server::receive(vector<uint8_t>& buffer)
{
    buffer.resize(MAXLINE);

    int n = ::recvfrom(sockfd, buffer.data(), MAXLINE, MSG_WAITALL, (sockaddr*)&cliaddr, (socklen_t*)&rec_socket_len);
    if(n < 0)
    {
        perror("SERVER socket: received -1 bytes");
        return n;
    }
    
    cout << "Received bytes: " << n << endl;
    buffer.resize(n);

    return n;
}