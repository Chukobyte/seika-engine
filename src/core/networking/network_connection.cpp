#include "network_connection.h"

#include "../signal_manager.h"

void TCPConnection::StartReadingNetworkMessages() {
    auto handleReadFunction = [this] (const asio::error_code &errorCode, size_t bytes) {
        if (!errorCode) {
            std::string message;
            int startBracketCounter = 0;
            for (unsigned int i = 0; i < bytes; i++) {
                message += networkBuffer[i];
                if (message.back() == '{') {
                    startBracketCounter++;
                } else if (message.back() == '}') {
                    startBracketCounter--;
                    if (startBracketCounter == 0) {
                        networkQueue.PushBack(NetworkMessage{.message = message});
                        message.clear();
                    }
                }
            }
            StartReadingNetworkMessages();
        } else if(errorCode == asio::error::eof || errorCode == asio::error::connection_reset || errorCode == asio::error::connection_aborted) {
            Disconnect();
//            logger->Warn("Connection closed!");
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "peer_disconnected", SignalArguments{});
        } else {
            Disconnect();
            logger->Error("Issues with connection: " + errorCode.message());
            SignalManager::GetInstance()->EmitSignal(NO_ENTITY, "peer_disconnected", SignalArguments{});
        }
    };
    socket.async_read_some(asio::buffer(networkBuffer.data(), networkBuffer.size()), handleReadFunction);
}
