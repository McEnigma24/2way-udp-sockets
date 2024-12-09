#pragma once
#include "udp_socket.hpp"

struct Udp_client;
struct Udp_server : public Udp_socket
{
    Udp_server(const string& ip, const uint32_t port);

    void wait_for_init_msg_than_resp(Udp_client* sender);
    void set_timeout(int seconds = 0, int microseconds = 0);
    int receive(vector<uint8_t>& buffer);
};
