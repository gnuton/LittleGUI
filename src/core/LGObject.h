#ifndef LITTLEGUI_LGOBJECT_H
#define LITTLEGUI_LGOBJECT_H

#include "Macros.h"
#include <memory>
#include <set>
#include <mutex>

using namespace std;

class LGObject : public enable_shared_from_this<LGObject> {
    NO_COPY_AND_ASSIGN(LGObject);

protected:
    LGObject(weak_ptr<LGObject> parent);

public:
    virtual ~LGObject();
    const string &getName() const;
    void setName(const string &name);

    const weak_ptr<LGObject> &getParent() const;
    void setParent(const weak_ptr<LGObject> &parent);

    bool hasChildren() const;

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
