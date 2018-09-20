#ifndef LITTLEGUI_LGOBJECT_H
#define LITTLEGUI_LGOBJECT_H

#include "Macros.h"
#include <memory>
#include <set>
#include <mutex>
#include <atomic>

class LGObject;
template <class T>
class ObjectBuilder {

public:
    static std::shared_ptr<T> create(std::weak_ptr<LGObject> parent = std::weak_ptr<LGObject>()) {
        auto instance = std::shared_ptr<T>(new T);
        instance->setParent(parent);
        return instance;
    }
};

class LGObject : public std::enable_shared_from_this<LGObject>, public ObjectBuilder<LGObject> {
    NO_COPY_AND_ASSIGN(LGObject);
    friend ObjectBuilder<LGObject>;

protected:
    LGObject();

public:
    virtual ~LGObject();
    const std::string &getName() const;
    void setName(const std::string &name);

    const std::weak_ptr<LGObject> &getParent() const;
    void setParent(const std::weak_ptr<LGObject> &parent);

    bool hasChildren() const;
    bool isChild(const std::weak_ptr<LGObject> &child) const;

private:
    bool removeChild(std::weak_ptr<LGObject> child);
    bool addChild(std::weak_ptr<LGObject> child);

private:
    std::string name_;
    std::weak_ptr<LGObject> parent_;
    std::set<std::shared_ptr<LGObject>> children_;
    std::mutex mtx_;
};

#endif //LITTLEGUI_LGOBJECT_H
