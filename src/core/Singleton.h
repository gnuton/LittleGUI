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
        if (!instance_)
            instance_ = std::shared_ptr<T>(new T(args...));
        return instance_;
    }

    static std::weak_ptr<T> getInstance(){
        if (!instance_)
            throw std::runtime_error("Please create an instance before calling getInstance");

        return instance_;
    }


    static void destroyInstance(){
        instance_ = std::shared_ptr<T>();
    }

private:
    static std::shared_ptr<T> instance_;
};

template <class T> std::shared_ptr<T>  Singleton<T>::instance_ = nullptr;

#endif //LITTLEGUI_SINGLETON_H
