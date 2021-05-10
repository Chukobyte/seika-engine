#include "network_tcp_client.h"
#include "../global_dependencies.h"

NetworkTCPClient::NetworkTCPClient(asio::io_context &context, const std::string &ipAddress, int port) : context(context), socket(context), ipAddress(ipAddress), port(port) {
    networkContext = GD::GetContainer()->networkContext;
    logger = Logger::GetInstance();
}

NetworkTCPClient::~NetworkTCPClient() {
    Disconnect();
}

void NetworkTCPClient::Connect() {
    if (!connection) {
        asio::error_code errorCode;
        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ipAddress.c_str(), errorCode), port);
        connection = networkContext->NewTCPConnection(context, networkQueue, NetworkConnectionHostType_CLIENT, 1);
        connection->GetSocket().connect(endpoint, errorCode);

        if (!errorCode) {
            logger->Debug("Connected to server successfully!");
            std::thread threadContext = std::thread([&]() {
                context.run();
            });

            connection->StartReadingNetworkMessages();

            // TODO: should be place in main loop (without sleep of course)
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1000000ms);

            context.stop();
            if (threadContext.joinable()) {
                threadContext.join();
            }
        } else {
            logger->Error("Client failed to connect!\n" + errorCode.message());
        }

    }
}

void NetworkTCPClient::Disconnect() {
    if (connection) {
        delete connection;
        connection = nullptr;
    }
}

void NetworkTCPClient::ProcessMessageQueue() {
    while (!networkQueue.IsEmpty()) {
        NetworkMessage networkMessage = networkQueue.PopFront();
    }
}
