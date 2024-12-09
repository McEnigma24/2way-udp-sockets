#include "udp_server.h"
#include "udp_client.h"

int main()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\nWs ready\n" << endl;

    Udp_server receiving_stats("127.0.0.2", 8080);
    Udp_client sending_reqs("127.0.0.1", 8080);

    sending_reqs.send_until_there_is_a_resp(&receiving_stats); // init msg

    vector<uint8_t> buffer;
    int req_num = 1;
    for(int i=0; i<3; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));

        buffer.resize(4);
        memcpy(&buffer[0], &req_num, sizeof(req_num));
        sending_reqs.send(buffer);

        cout << "Req: " << req_num << " SENT" << endl;
        req_num++;

        cout << "waiting for stats" << endl;
        receiving_stats.receive(buffer);
        long long received_stats{};
        memcpy(&received_stats, &buffer[0], sizeof(received_stats));

        cout << "Received: ";
        log(received_stats);
    }

    return 0;
}