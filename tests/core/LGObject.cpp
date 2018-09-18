#include <iostream>
#include <thread>
#include <numeric>

#include <catch.hpp>
#include <core/LGObject.h>

class MyObj : public ObjectBuilder<MyObj>, public LGObject {
    NO_COPY_AND_ASSIGN(MyObj)

    friend ObjectBuilder<MyObj>;
protected:
    MyObj() : LGObject() {}

public:
    using ObjectBuilder<MyObj>::create;
};

class MyChildObj : public ObjectBuilder<MyChildObj>, public MyObj {
    NO_COPY_AND_ASSIGN(MyChildObj)

    friend ObjectBuilder<MyChildObj>;
protected:
    MyChildObj() : MyObj() {}

public:
    using ObjectBuilder<MyChildObj>::create;

    bool methodA() { return true; }
};

class MyChildObj2 : public ObjectBuilder<MyChildObj2>, public MyChildObj {
    NO_COPY_AND_ASSIGN(MyChildObj2)

    friend ObjectBuilder<MyChildObj2>;

protected:
    MyChildObj2() : MyChildObj() {};

public:
    using ObjectBuilder<MyChildObj2>::create;

    bool methodB() { return true; }
};

TEST_CASE ("Check that create static method works along with inheritance") {
    auto parent = MyObj::create();
    auto child1 = MyChildObj::create(parent);
    auto child2 = MyChildObj2::create(child1);

    REQUIRE(child1->methodA());
    REQUIRE(child2->methodB());
}

// ?????
TEST_CASE("Check casting with static_pointer_cast ") {
    auto parent = MyObj::create();
    auto castedChild = std::static_pointer_cast<MyChildObj2>(parent);
    REQUIRE(castedChild->methodB());
    REQUIRE(parent.use_count() == 2);
    REQUIRE(castedChild.get() == parent.get());
}

TEST_CASE("Check parent getter/setter and that parent in constructor is correcly set") {
    auto parent = MyObj::create();
    auto child = MyObj::create(parent);

    REQUIRE(parent->getParent().expired());
    REQUIRE(child->getParent().lock() == parent);
}


TEST_CASE("Check name getter and setters") {
    auto parent = MyObj::create();
    const std::string name = "TEST";
    parent->setName(name);
    REQUIRE(parent->getName() == name);
}

TEST_CASE("Children gets automatically destroyed when parent is destroyed") {
    std::weak_ptr<LGObject> child1;
    std::weak_ptr<LGObject> child2;
    // Scope where the parents live
    {
        auto parent = MyObj::create();
        child1 = MyObj::create(parent);
        child2 = MyObj::create(child1);
    }
    REQUIRE(child1.expired() == true);
    REQUIRE(child2.lock() == std::shared_ptr<LGObject>());
}

TEST_CASE("Check that children are added to parent") {
    auto parent = MyObj::create();
    REQUIRE_FALSE(parent.get()->hasChildren());

    auto child1 = MyObj::create(parent);
    auto child2 = MyObj::create(parent);
    REQUIRE(parent.get()->hasChildren());
}

TEST_CASE("If the parent shared_ptr is lost, it and its children get destroyed") {
    std::weak_ptr<LGObject> parent = MyObj::create();
    std::weak_ptr<LGObject> child1 = MyObj::create(parent);
    REQUIRE(parent.lock().use_count() == 0);
    REQUIRE(child1.lock().use_count() == 0);
    REQUIRE(parent.expired());
    REQUIRE(child1.expired());
}

TEST_CASE("Children obj shared_ptrs must be hold just by the parent and just once.") {
    auto parent = MyObj::create();
    std::weak_ptr<LGObject> child1 = MyObj::create(parent);
    std::weak_ptr<LGObject> child2 = MyObj::create(parent);
    std::weak_ptr<LGObject> child3 = MyObj::create(parent);

    REQUIRE(parent.use_count() == 1);
    REQUIRE(child1.lock().use_count() == 2); // 2 => 1 is shared_ptr is child1.lock() + 1 in parent::children
}

TEST_CASE("Check that isChild works") {
    auto parent = MyObj::create();
    auto notAChild = MyObj::create();
    auto child1 = MyObj::create(parent);
    REQUIRE(parent->isChild(child1));
    REQUIRE_FALSE(parent->isChild(notAChild));
}

//
TEST_CASE("Testing mutex for setParent ") {
    auto parent1 = MyObj::create();
    auto parent2 = MyObj::create();
    auto child = MyObj::create(parent1);

    int n = 100; // NOTE this should be big enough to generate some clashes which can be handled by mutexes
    int i = n;
    //int count = 0;

    while (--i) {
        std::vector<std::thread *> threads;
        int j = n;
        auto l = [&]() {
            const auto p = child->getParent().lock();
            //cout << i << " " << j << " Parent " << p << endl;
            //count += (p == parent1) ? 1 : -1;
            child->setParent(p == parent1 ? parent2 : parent1);
        };
        while (--j) threads.push_back(new std::thread(l));
        for (auto t : threads) t->join();
        for (auto t : threads) delete t;
    }
    //REQUIRE(count == 0); /// this check is not reliable
}