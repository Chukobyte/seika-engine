#include <iostream>
#include <asio.hpp>
#include "core/networking/network_tcp_server.h"

int main() {
    asio::io_context context;

    NetworkTCPServer *server = new NetworkTCPServer(context, 55555);
    server->Start();


    return 0;
}
