#include "LGObject.h"
#include <iostream>

LGObject::LGObject(weak_ptr<LGObject> parent) {
    setParent(parent);
}

LGObject::~LGObject() {
}

const string &LGObject::getName() const {
    return name;
}

void LGObject::setName(const string &name) {
    LGObject::name = name;
}

const weak_ptr<LGObject> LGObject::getParent() const {
    return parent;
}

void LGObject::setParent(const weak_ptr<LGObject> &parent) {
    LGObject::parent = parent.lock();
}

