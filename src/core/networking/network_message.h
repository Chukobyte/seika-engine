#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <vector>
#include <ostream>

template <typename T>
struct NetworkMessageHeader {
    T id{};
    uint32_t size = 0;
};

template <typename T>
struct NetworkMessage {
    NetworkMessageHeader<T> header{};
    std::vector<uint8_t> body;

    size_t size() const {
        return sizeof(NetworkMessageHeader<T>) + body.size();
    }

    friend std::ostream& operator << (std::ostream &os, const NetworkMessage<T> &message) {
        os << "ID:" << int(message.header.id) << " Size:" << message.header.size;
        return os;
    }
};

#endif //NETWORK_MESSAGE_H
