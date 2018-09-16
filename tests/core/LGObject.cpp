#include <catch.hpp>
#include <core/LGObject.h>
#include <iostream>

class MyObj : public ObjectBuilder<MyObj>, public LGObject {
    friend ObjectBuilder<MyObj>;
protected:
    MyObj() : LGObject() {}

public:
    using ObjectBuilder<MyObj>::create;
};

class MyChildObj : public ObjectBuilder<MyChildObj>, public MyObj {
    friend ObjectBuilder<MyChildObj>;
protected:
    MyChildObj() : MyObj() {}

public:
    using ObjectBuilder<MyChildObj>::create;
    bool methodA() {return true;}
};

class MyChildObj2 : public ObjectBuilder<MyChildObj2>, public MyChildObj {
    friend ObjectBuilder<MyChildObj2>;

protected:
    MyChildObj2() : MyChildObj() {};

public:
    using ObjectBuilder<MyChildObj2>::create;
    bool methodB() {return true;}
};

TEST_CASE ("Check that create static method works along with inheritance") {
    auto parent = MyObj::create();
    auto child1 = MyChildObj::create(parent);
    auto child2 = MyChildObj2::create(child1);

    REQUIRE(child1->methodA());
    REQUIRE(child2->methodB());
}

TEST_CASE("Check casting with static_pointer_cast") {
    auto parent = MyObj::create();
    auto castedChild = static_pointer_cast<MyChildObj2>(parent);
    REQUIRE(castedChild->methodB());
    REQUIRE(parent.use_count() == 2);
    REQUIRE(castedChild.get() == parent.get());
}

TEST_CASE("Check parent getter/setter and that parent in constructor is correcly set") {
    auto parent = MyObj::create();
    auto child = MyObj::create(parent);

    const weak_ptr<LGObject> expectedParent = weak_ptr<LGObject>();
    REQUIRE(parent->getParent().lock() == expectedParent.lock());
    REQUIRE(child->getParent().lock() == parent);
}


TEST_CASE("Check name getter and setters") {
    auto parent = MyObj::create();
    const string name = "TEST";
    parent->setName(name);
    REQUIRE(parent->getName() == name);
}

TEST_CASE("Children gets automatically destroyed when parent is destroyed") {
    weak_ptr<LGObject> child1;
    weak_ptr<LGObject> child2;
    // Scope where the parents live
    {
        auto parent = MyObj::create();
        child1 = MyObj::create(parent);
        child2 = MyObj::create(child1);
    }
    REQUIRE(child1.expired() == true);
    REQUIRE(child2.lock() == shared_ptr<LGObject>());
}

TEST_CASE("Check that children are added to parent") {
    auto parent = MyObj::create();
    REQUIRE_FALSE(parent.get()->hasChildren());

    auto child1 = MyObj::create(parent);
    auto child2 = MyObj::create(parent);
    REQUIRE(parent.get()->hasChildren());
}

TEST_CASE("If the parent shared_ptr is lost, it and its children get destroyed") {
    weak_ptr<LGObject> parent = MyObj::create();
    weak_ptr<LGObject> child1 = MyObj::create(parent);
    REQUIRE(parent.lock().use_count() == 0);
    REQUIRE(child1.lock().use_count() == 0);
    REQUIRE(parent.expired());
    REQUIRE(child1.expired());
}

TEST_CASE("Parent object must not have any shared_ptr reference in its children") {
    auto parent = MyObj::create();
    weak_ptr<LGObject> child1 = MyObj::create(parent);
    weak_ptr<LGObject> child2 = MyObj::create(parent);
    weak_ptr<LGObject> child3 = MyObj::create(parent);

    REQUIRE(parent.use_count() == 1);
    REQUIRE(child1.lock().use_count() == 1);
}