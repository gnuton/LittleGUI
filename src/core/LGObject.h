#ifndef LITTLEGUI_LGOBJECT_H
#define LITTLEGUI_LGOBJECT_H

#include "Macros.h"
#include <memory>
#include <set>
#include <mutex>
#include <atomic>

using namespace std;

class LGObject;
template <class T>
class ObjectBuilder {

public:
    static shared_ptr<T> create(weak_ptr<LGObject> parent = weak_ptr<LGObject>()) {
        auto instance = shared_ptr<T>(new T);
        instance->setParent(parent);
        return instance;
    }
};

class LGObject : public enable_shared_from_this<LGObject>, public ObjectBuilder<LGObject> {
    NO_COPY_AND_ASSIGN(LGObject);
    friend ObjectBuilder<LGObject>;

protected:
    LGObject();

public:
    virtual ~LGObject();
    const string &getName() const;
    void setName(const string &name);

    const weak_ptr<LGObject> &getParent() const;
    void setParent(const weak_ptr<LGObject> &parent);

    bool hasChildren() const;
    bool isChild(const weak_ptr<LGObject> &child) const;

private:
    bool removeChild(weak_ptr<LGObject> child);
    bool addChild(weak_ptr<LGObject> child);

private:
    string name;
    weak_ptr<LGObject> parent;
    set<shared_ptr<LGObject>> children;

    mutex mtx;
};


#endif //LITTLEGUI_LGOBJECT_H
