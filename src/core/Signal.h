// This code has been written by Simon Schneegans
// http://simmesimme.github.io/tutorials/2015/09/20/signal-slot
#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <map>
#include "Macros.h"

/** A signal object may call multiple slots with the
 *  same signature. You can connect functions to the signal
 *  which will be called when the emit() method on the
 * signal object is invoked. Any argument passed to emit()
 * will be passed to the given functions.
 *
 * Usage:
 * # Define signal
 * TODO
 *
 * # Define slot
 * TODO
 *
 * # Connect signal and slots together
 * TODO
 *
 * # Emit signal
 * TODO
 */
template <typename... Args>
class Signal {

public:
    NO_COPY_AND_ASSIGN(Signal)

    Signal() : current_id_(0), slots_(new std::map<int, std::function<void(Args...)>>) {}
    ~Signal() { delete slots_; }

    // connects a member function to this Signal
    template <typename T>
    int connectMember(T *inst, void (T::*func)(Args...)) {
        return connect([=](Args... args) {
            (inst->*func)(args...);
        });
    }

    // connects a const member function to this Signal
    template <typename T>
    int connectMember(T *inst, void (T::*func)(Args...) const) {
        return connect([=](Args... args) {
            (inst->*func)(args...);
        });
    }

    // connects a std::function to the signal. The returned
    // value can be used to disconnect the function again
    int connect(std::function<void(Args...)> const& slot) const {
        slots_->insert(std::make_pair(++current_id_, slot));
        return current_id_;
    }

    // disconnects a previously connected function
    void disconnect(int id) const {
        slots_->erase(id);
    }

    // disconnects all previously connected functions
    void disconnectAll() const {
        slots_->clear();
    }

    // calls all connected functions
    void emit(Args... p) {

        for(auto it : *slots_) {
            try {
                it.second(p...);
            } catch (const std::exception& e) {
                //WARN_LOG("Failed to call the slot! Problem:" << e.what());
            }
        }
    }

private:
    mutable std::map<int, std::function<void(Args...)>> *slots_;
    mutable int current_id_;
};

#endif
