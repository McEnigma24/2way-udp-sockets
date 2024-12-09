#include "udp_server.h"
#include "udp_client.h"

int main()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\nAhti ready \n" << endl;

    Udp_client sending_stats("127.0.0.2", 8080);
    Udp_server receiving_reqs("127.0.0.1", 8080);

    receiving_reqs.wait_for_init_msg_than_resp(&sending_stats); // init msg

    vector<uint8_t> buffer;
    for(int i=0; i<3; i++)
    {
        cout << "waiting for req" << endl;
        receiving_reqs.receive(buffer);

        log(buffer.size());
        int received_req;
        memcpy(&received_req, &buffer[0], sizeof(received_req));
        log(received_req);
        cout << endl;

        cout << "REQ received -> sending stats" << endl;

        buffer.resize(8);
        long long stats_to_send = 100000000 + received_req;
        memcpy(&buffer[0], &stats_to_send, sizeof(stats_to_send));
        log(stats_to_send);

        sending_stats.send(buffer);
        cout << "Stats SENT" << endl;

        this_thread::sleep_for(chrono::milliseconds(3000));
    }

    return 0;
}