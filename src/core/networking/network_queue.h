#ifndef NETWORK_QUEUE_H
#define NETWORK_QUEUE_H

#include <string>

#include "network_common.h"

struct NetworkMessage {
    std::string message;
};

template <typename T>
class NetworkQueue {
  protected:
    std::mutex queueMutex;
    std::deque<T> queue;
    std::condition_variable conditionVariableBlocking;
    std::mutex blockingMutex;
  public:
    NetworkQueue() = default;
    NetworkQueue(const NetworkQueue<T>&) = delete;
    virtual ~NetworkQueue() {
        Clear();
    }

    const T& Front() {
        queueMutex.lock();
        auto t = queue.front();
        queueMutex.unlock();
        return t;
    }

    const T& Back() {
        queueMutex.lock();
        auto t = queue.back();
        queueMutex.unlock();
        return t;
    }

    T PopFront() {
        queueMutex.lock();
        auto t = std::move(queue.front());
        queue.pop_front();
        queueMutex.unlock();
        return t;
    }

    T PopBack() {
        queueMutex.lock();
        auto t = std::move(queue.back());
        queue.pop_back();
        queueMutex.unlock();
        return t;
    }

    void PushFront(const T& item) {
        queueMutex.lock();
        queue.emplace_front(std::move(item));
        queueMutex.unlock();

        std::unique_lock<std::mutex> uniqueLock(blockingMutex);
        conditionVariableBlocking.notify_one();
    }

    void PushBack(const T& item) {
        queueMutex.lock();
        queue.emplace_back(std::move(item));
        queueMutex.unlock();

        std::unique_lock<std::mutex> uniqueLock(blockingMutex);
        conditionVariableBlocking.notify_one();
    }

    bool IsEmpty() {
        queueMutex.lock();
        bool empty = queue.empty();
        queueMutex.unlock();
        return empty;
    }

    size_t Size() {
        queueMutex.lock();
        size_t size = queue.size();
        queueMutex.unlock();
        return size;
    }

    void Clear() {
        queueMutex.lock();
        queue.clear();
        queueMutex.unlock();
    }

    void Wait() {
        while (IsEmpty()) {
            std::unique_lock<std::mutex> uniqueLock(blockingMutex);
            conditionVariableBlocking.wait(uniqueLock);
        }
    }
};

#endif //NETWORK_QUEUE_H
