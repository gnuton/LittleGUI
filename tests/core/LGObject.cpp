#include <catch.hpp>
#include <core/LGObject.h>
#include <iostream>

class MyObj : public LGObject {
public:
    MyObj(weak_ptr<LGObject> parent = weak_ptr<LGObject>()): LGObject(parent) {}
    ~MyObj() {}
    bool isWidget() const { return false; }
    bool isWindow() const { return false; }
};

TEST_CASE("Check parent getter/setter and that parent in constructor is correcly set") {
    auto parent = make_shared<MyObj>();
    auto child =  make_shared<MyObj>(parent);

    const weak_ptr<LGObject> expectedParent = weak_ptr<LGObject>();
    REQUIRE(parent->getParent().lock() == expectedParent.lock());
    REQUIRE(child->getParent().lock() == parent);
}


TEST_CASE("Check name getter and setters") {
    auto parent = make_shared<MyObj>();
    const string name = "TEST";
    parent->setName(name);
    REQUIRE(parent->getName() == name);
}

TEST_CASE("Children gets automatically destroyed when parent is destroyed") {
    weak_ptr<LGObject> child1;
    weak_ptr<LGObject> child2;
    // Scope where the parents live
    {
        auto parent = make_shared<MyObj>();
        child1 = make_shared<MyObj>(parent);
        child2 = make_shared<MyObj>(child1);
    }
    REQUIRE(child1.expired() == true);
    REQUIRE(child2.lock() == shared_ptr<LGObject>());
}

TEST_CASE("Check that children are added to parent") {
    auto parent = make_shared<MyObj>();
    REQUIRE_FALSE(parent.get()->hasChildren());

    auto child1 = make_shared<MyObj>(parent);
    auto child2 = make_shared<MyObj>(parent);
    REQUIRE(parent.get()->hasChildren());
}

TEST_CASE("If the parent shared_ptr is lost, it and its children get destroyed") {
    weak_ptr<LGObject> parent = make_shared<MyObj>();
    weak_ptr<LGObject> child1 = make_shared<MyObj>(parent);
    REQUIRE(parent.lock().use_count() == 0);
    REQUIRE(child1.lock().use_count() == 0);
    REQUIRE(parent.expired());
    REQUIRE(child1.expired());
}

TEST_CASE("Parent object must not have any shared_ptr reference in its children") {
    auto parent = make_shared<MyObj>();
    weak_ptr<LGObject> child1 = make_shared<MyObj>(parent);
    weak_ptr<LGObject> child2 = make_shared<MyObj>(parent);
    weak_ptr<LGObject> child3 = make_shared<MyObj>(parent);

    REQUIRE(parent.use_count() == 1);
    REQUIRE(child1.lock().use_count() == 1);
}