#ifndef LITTLEGUI_SINGLETON_H
#define LITTLEGUI_SINGLETON_H

#include <utility>
#include <stdexcept>
#include <memory>

template <class T>
class Singleton{
public:
    template <typename... Args>
    static std::weak_ptr<T> createInstance(Args... args){
        if (!instance)
            instance = std::shared_ptr<T>(new T(args...));
        return instance;
    }

    static std::weak_ptr<T> getInstance(){
        if (!instance)
            throw std::runtime_error("Please create an instance before calling getInstance");

        return instance;
    }


    static void destroyInstance(){
        instance = std::shared_ptr<T>();
    }

private:
    static std::shared_ptr<T> instance;
};

template <class T> std::shared_ptr<T>  Singleton<T>::instance = nullptr;

#endif //LITTLEGUI_SINGLETON_H
