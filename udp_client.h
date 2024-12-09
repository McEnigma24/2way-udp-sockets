#pragma once
#include "udp_socket.hpp"

struct Udp_server;
struct Udp_client : public Udp_socket
{
    Udp_client(const string& ip, const uint32_t port);

    void send_until_there_is_a_resp(Udp_server* receiver);
    int send(const uint8_t* buffer, const size_t length) const;
    int send(const vector<uint8_t>& buffer) const;
};