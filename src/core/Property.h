// Code taken from http://simmesimme.github.io/tutorials/2015/09/21/properties
#ifndef LITTLEGUI_PROPERTY_H
#define LITTLEGUI_PROPERTY_H


#include "Signal.h"
#include <iostream>

// A Property is a encpsulates a value and may inform
// you on any changes applied to this value.

template <typename T>
class Property {

public:
    typedef T value_type;

    // Properties for built-in types are automatically
    // initialized to 0. See template spezialisations
    // at the bottom of this file
    Property()
            : connection_(nullptr)
            , connectionId_(-1) {}

    Property(T const& val)
            : value_(val)
            , connection_(nullptr)
            , connectionId_(-1) {}

    Property(T&& val)
            : value_(std::move(val))
            , connection_(nullptr)
            , connectionId_(-1) {}
    Property(Property<T> const& to_copy)
            : value_(to_copy.value_)
            , connection_(nullptr)
            , connectionId_(-1) {}

    Property(Property<T>&& to_copy)
            : value_(std::move(to_copy.value_))
            , connection_(nullptr)
            , connectionId_(-1) {}

    // returns a Signal which is fired when the internal value
    // will be changed. The old value is passed as parameter.
    virtual Signal<T> const& before_change() const { return beforeChange_; }

    // returns a Signal which is fired when the internal value
    // has been changed. The new value is passed as parameter.
    virtual Signal<T> const& onChange() const { return onChange_; }

    // sets the Property to a new value. before_change() and
    // onChange() will be emitted.
    virtual void set(T const& value) {
        if (value != value_) {
            beforeChange_.emit(value_);
            value_ = value;
            onChange_.emit(value_);
        }
    }

    // sets the Property to a new value. before_change() and
    // onChange() will not be emitted
    void set_with_no_emit(T const& value) {
        value_ = value;
    }

    // emits before_change() and onChange() even if the value
    // did not change
    void touch() {
        beforeChange_.emit(value_);
        onChange_.emit(value_);
    }

    // returns the internal value
    virtual T const& get() const { return value_; }

    // connects two Properties to each other. If the source's
    // value is changed, this' value will be changed as well
    virtual void connectFrom(Property<T> const &source) {
        disconnect();
        connection_ = &source;
        connectionId_ = source.onChange().connect([this](T const& value){
            set(value);
            return true;
        });
        set(source.get());
    }

    // if this Property is connected from another property,
    // it will e disconnected
    virtual void disconnect() {
        if (connection_) {
            connection_->onChange().disconnect(connectionId_);
            connectionId_ = -1;
            connection_ = nullptr;
        }
    }

    // if there are any Properties connected to this Property,
    // they won't be notified of any further changes
    virtual void disconnect_auditors() {
        onChange_.disconnectAll();
        beforeChange_.disconnectAll();
    }

    // assigns the value of another Property
    virtual Property<T>& operator=(Property<T> const& rhs) {
        set(rhs.value_);
        return *this;
    }

    // assigns a new value to this Property
    virtual Property<T>& operator=(T const& rhs) {
        set(rhs);
        return *this;
    }

    // compares the values of two Properties
    bool operator==(Property<T> const& rhs) const {
        return Property<T>::get() == rhs.get();
    }
    bool operator!=(Property<T> const& rhs) const {
        return Property<T>::get() != rhs.get();
    }

    // compares the values of the Property to another value
    bool operator==(T const& rhs) const { return Property<T>::get() == rhs; }
    bool operator!=(T const& rhs) const { return Property<T>::get() != rhs; }

    // returns the value of this Property
    T const& operator()() const { return Property<T>::get(); }

private:
    Signal<T> onChange_;
    Signal<T> beforeChange_;

    Property<T> const* connection_;
    int connectionId_;
    T value_;
};

// specialization for built-in default contructors
template<> inline Property<double>::Property()
        : connection_(nullptr), connectionId_(-1), value_(0.0) {}

template<> inline Property<float>::Property()
        : connection_(nullptr), connectionId_(-1), value_(0.f) {}

template<> inline Property<short>::Property()
        : connection_(nullptr), connectionId_(-1), value_(0) {}

template<> inline Property<int>::Property()
        : connection_(nullptr), connectionId_(-1), value_(0) {}

template<> inline Property<char>::Property()
        : connection_(nullptr), connectionId_(-1), value_(0) {}

template<> inline Property<unsigned>::Property()
        : connection_(nullptr), connectionId_(-1), value_(0) {}

template<> inline Property<bool>::Property()
        : connection_(nullptr), connectionId_(-1), value_(false) {}

// stream operators
template<typename T>
std::ostream& operator<<(std::ostream& outStream, Property<T> const& val) {
    outStream << val.get();
    return outStream;
}

template<typename T>
std::istream& operator>>(std::istream& inStream, Property<T>& val) {
    T tmp;
    inStream >> tmp;
    val.set(tmp);
    return inStream;
}

#endif //LITTLEGUI_PROPERTY_H
