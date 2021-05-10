#include <asio.hpp>
#include "core/networking/network_tcp_server.h"
#include "core/networking/network_tcp_client.h"

const int SERVER_PORT = 55555;

int main() {
    asio::io_context context;

    NetworkTCPServer *server = new NetworkTCPServer(context, SERVER_PORT);
    server->Start();

//    NetworkTCPClient *client = new NetworkTCPClient(context, "127.0.0.1", SERVER_PORT);
//    client->Connect();


    return 0;
}
