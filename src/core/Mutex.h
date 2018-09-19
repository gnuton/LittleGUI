#ifndef LITTLEGUI_MUTEX_H
#define LITTLEGUI_MUTEX_H

#include <mutex>
#include <thread>

class mutex :
        public std::mutex
{
public:
#ifndef NDEBUG
    void lock()
    {
        std::mutex::lock();
        m_holder = std::this_thread::get_id();
    }
#endif // #ifndef NDEBUG

#ifndef NDEBUG
    void unlock()
    {
        m_holder = std::thread::id();
        std::mutex::unlock();
    }
#endif // #ifndef NDEBUG

#ifndef NDEBUG
    /**
    * @return true iff the mutex is locked by the caller of this method. */
    bool locked_by_caller() const
    {
        return m_holder == std::this_thread::get_id();
    }
#endif // #ifndef NDEBUG

private:
#ifndef NDEBUG
    std::thread::id m_holder;
#endif // #ifndef NDEBUG
};

#endif //LITTLEGUI_MUTEX_H
