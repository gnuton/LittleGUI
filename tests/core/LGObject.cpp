#include <catch.hpp>
#include <core/LGObject.h>
#include <iostream>

TEST_CASE( "Check parent getter/setter and that parent in constructor is correcly set" ) {
    class MyObj : public LGObject {

    public:
        MyObj(weak_ptr<LGObject> parent = weak_ptr<LGObject>()): LGObject(parent){}
        ~MyObj(){}
        bool isWidget() const { return false; }
        bool isWindow() const { return false; }
    };

    auto parent = make_shared<MyObj>();
    auto child = make_shared<MyObj>(parent);
    const weak_ptr<LGObject> expectedParent = weak_ptr<LGObject>();
    REQUIRE(parent->getParent().lock() == expectedParent.lock());
    REQUIRE(child->getParent().lock() == parent);
}