#ifndef LITTLEGUI_LGOBJECT_H
#define LITTLEGUI_LGOBJECT_H

#include "Macros.h"
#include <memory>

using namespace std;

class LGObject {
    NO_COPY_AND_ASSIGN(LGObject);

protected:
    LGObject(weak_ptr<LGObject> parent); // This class is abstract

public:
    virtual ~LGObject();
    const string &getName() const;
    void setName(const string &name);
    const weak_ptr<LGObject> getParent() const;
    void setParent(const weak_ptr<LGObject> &parent);

private:
    string name;
    shared_ptr<LGObject> parent;
};


#endif //LITTLEGUI_LGOBJECT_H
