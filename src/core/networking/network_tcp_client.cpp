#include "network_tcp_client.h"

NetworkTCPClient::NetworkTCPClient(asio::io_context &context, const std::string ipAddress, int port) : socket(context) {}