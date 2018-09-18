#include "LGObject.h"
#include <iostream>

LGObject::LGObject() {
}

LGObject::~LGObject() {
}

const std::string &LGObject::getName() const {
    return name;
}

void LGObject::setName(const std::string &name) {
    LGObject::name = name;
}

const std::weak_ptr<LGObject> &LGObject::getParent() const {
    return parent;
}

void LGObject::setParent(const std::weak_ptr<LGObject> &parent) {
    std::lock_guard<std::mutex> lock(mtx);

    if (LGObject::parent.lock() == parent.lock())
        return;

    LGObject::parent = parent;
    if (!parent.expired())
        parent.lock()->addChild(shared_from_this());
}

bool LGObject::removeChild(std::weak_ptr<LGObject> child) {
    //lock_guard<mutex> lock(mtx);
    return !child.expired() && children.erase(child.lock());
}

bool LGObject::addChild(std::weak_ptr<LGObject> child) {
    //lock_guard<mutex> lock(mtx);

    if (child.expired())
        return false;
    children.insert(child.lock());
    return true;
}

bool LGObject::hasChildren() const {
    return children.size();
}

bool LGObject::isChild(const std::weak_ptr<LGObject> &child) const {
    if (child.expired())
        return false;
    return (children.find(child.lock()) != children.end());
}


