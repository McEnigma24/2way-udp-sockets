#include "udp_client.h"
#include "udp_server.h"


Udp_client::Udp_client(const string& ip, const uint32_t port)
    :Udp_socket(ip, port)
{
    // does not garuantee that the other side it listening

    // int result = -1;
    // do
    // {
    //     result = ::connect(sockfd, (const sockaddr*)&servaddr, rec_socket_len);
    // }
    // while(result != 0);
}

void Udp_client::send_until_there_is_a_resp(Udp_server* receiver)
{
    receiver->set_timeout(1, 0);

    vector<uint8_t> buffer;
    int result = -1;
    do
    {
        send(buffer);
        result = receiver->receive(buffer);
    }
    while(result == -1);

    receiver->set_timeout();

    cout << "INT - completed\n";
}

int Udp_client::send(const uint8_t* buffer, const size_t length) const
{
    int result = ::sendto(sockfd, buffer, length, MSG_CONFIRM, (const sockaddr*)&servaddr, sizeof(servaddr));
    if(result < 0)
    {
        perror("CLIENT socket: error when sending");
    }

    return result;
}

int Udp_client::send(const vector<uint8_t>& buffer) const
{
    send(buffer.data(), buffer.size());
}