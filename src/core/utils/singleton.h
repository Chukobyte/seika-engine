#pragma once

template <typename T>
class Singleton {
  public:
    static T* GetInstance();
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;
  protected:
    struct singleton {};
    Singleton() = default;
};

template <typename T>
T* Singleton<T>::GetInstance() {
    static T* instance = new T(singleton{});
    return instance;
}
