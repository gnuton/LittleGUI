#include <catch.hpp>
#include <core/Singleton.h>
#include <core/Macros.h>
#include <string>
#include <iostream>

class SingletonTest: public Singleton<SingletonTest> {
    friend class Singleton<SingletonTest>;
    NO_COPY_AND_ASSIGN(SingletonTest);

protected:
    SingletonTest() {};
    SingletonTest(const std::string& msg) {  msg_ = msg; };

public:
    bool methodA() { return true; }
    const std::string& methodB() { return msg_; }

private:
    std::string msg_;
};

namespace SingletonTestNS {
    void tearDown() {
        SingletonTest::destroyInstance();
    }
};

TEST_CASE("Check Sinlgeton create instance returns a valid weak ptr") {
    auto s = SingletonTest::createInstance();
    REQUIRE_FALSE(s.expired());
    REQUIRE(s.lock()->methodA());
    SingletonTestNS::tearDown();
}

TEST_CASE("Check Sinlgeton create instance with args returns a valid weak ptr") {
    SingletonTest::destroyInstance();
    auto s = SingletonTest::createInstance(std::string("AA"));
    REQUIRE_FALSE(s.expired());
    REQUIRE(s.lock()->methodA());
    REQUIRE(s.lock()->methodB() == "AA");
    SingletonTestNS::tearDown();
}

TEST_CASE("Check Sinlgeton get instance reurns a valid weak ptr") {
    SingletonTest::destroyInstance();
    auto s = SingletonTest::createInstance();
    auto w = SingletonTest::getInstance();
    REQUIRE_FALSE(w.expired());
    REQUIRE(w.lock()->methodA());
    SingletonTestNS::tearDown();
}

TEST_CASE("Check Sinlgeton destroy instance") {
    SingletonTest::destroyInstance();
    auto s = SingletonTest::createInstance();
    REQUIRE_FALSE(s.expired());
    SingletonTest::destroyInstance();
    REQUIRE(s.expired());
    REQUIRE_THROWS_WITH(SingletonTest::getInstance(), "Please create an instance before calling getInstance");
    SingletonTestNS::tearDown();
}

