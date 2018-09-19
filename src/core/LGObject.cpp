#include "LGObject.h"
#include <iostream>

LGObject::LGObject() {
}

LGObject::~LGObject() {
}

const std::string &LGObject::getName() const {
    return name_;
}

void LGObject::setName(const std::string &name) {
    LGObject::name_ = name;
}

const std::weak_ptr<LGObject> &LGObject::getParent() const {
    return parent_;
}

void LGObject::setParent(const std::weak_ptr<LGObject> &parent) {
    std::lock_guard<std::mutex> lock(mtx_);

    if (LGObject::parent_.lock() == parent.lock())
        return;

    LGObject::parent_ = parent;
    if (!parent.expired())
        parent.lock()->addChild(shared_from_this());
}

bool LGObject::removeChild(std::weak_ptr<LGObject> child) {
    //lock_guard<mutex> lock(mtx);
    return !child.expired() && children_.erase(child.lock());
}

bool LGObject::addChild(std::weak_ptr<LGObject> child) {
    //lock_guard<mutex> lock(mtx);

    if (child.expired())
        return false;
    children_.insert(child.lock());
    return true;
}

bool LGObject::hasChildren() const {
    return children_.size();
}

bool LGObject::isChild(const std::weak_ptr<LGObject> &child) const {
    if (child.expired())
        return false;
    return (children_.find(child.lock()) != children_.end());
}


