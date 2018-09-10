#include "Object.h"


Object::Object(Object *parent){
    setParent(parent);
}

Object::~Object() {
    disconnectAll();

    for (auto child : children) {
        delete child;
    }
    children.clear();
}

const Object* Object::getParent() const {
    return this->parent;
}

void Object::setParent(Object* parent) {
    //std::lock_guard<std::mutex> lock(mtx);
    if (this->parent)
        parent->removeChild(this);

    this->parent = parent;
    if (this->parent)
        this->parent->addChild(this);
}

bool Object::removeChild(Object* child) {
    //std::lock_guard<std::mutex> lock(mtx);
    if (!child)
        return false;
    return children.erase(child);
}

bool Object::addChild(Object* child) {
    //std::lock_guard<std::mutex> lock(mtx);
    if (!child)
        return false;
    this->children.insert(child);
    /* Disconnect all previous objs and connect just the new one */
    child->disconnectAll();
    child->requestDestroy.connectMember(this, &Object::onRequestChildDestroy);
    return true;
}

void Object::destroy() {
    //std::lock_guard<std::mutex> lock(mtx);
    requestDestroy.emit(this);
}

void Object::onRequestChildDestroy(Object* child) {
    //std::lock_guard<std::mutex> lock(mtx);
    if (children.find(child) == children.end()){
        return;
    }

    bool removed = removeChild(child);
    child->destroying.emit(child);
}

void Object::disconnectAll() {
    //std::lock_guard<std::mutex> lock(mtx);
    destroying.disconnectAll();
    requestDestroy.disconnectAll();
}

void Object::tick() {
    for (auto child : children) {
        child->tick();
    }
}
