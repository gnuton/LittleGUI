#include "LGObject.h"
#include <iostream>

LGObject::LGObject() {
}

LGObject::~LGObject() {
}

const string &LGObject::getName() const {
    return name;
}

void LGObject::setName(const string &name) {
    LGObject::name = name;
}

const weak_ptr<LGObject> &LGObject::getParent() const {
    return parent;
}

void LGObject::setParent(const weak_ptr<LGObject> &parent) {
    lock_guard<mutex> lock(mtx);
    LGObject::parent = parent;
}

bool LGObject::removeChild(weak_ptr<LGObject> child) {
    lock_guard<mutex> lock(mtx);
    return !child.expired() && children.erase(child.lock());
}

bool LGObject::addChild(weak_ptr<LGObject> child) {
    lock_guard<mutex> lock(mtx);

    if (child.expired())
        return false;
    children.insert(child.lock());
    return true;
}

bool LGObject::hasChildren() const {
    return children.size();
}


