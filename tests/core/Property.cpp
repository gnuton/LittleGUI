#include <catch.hpp>
#include <core/Property.h>

#include <sstream>

TEST_CASE("Check that connected slots are notified when a property value is changed") {
    Property<int> Integer(0);
    int res = 0, expected = 42;

    Integer.onChange().connect([&](int val) { res = val; });
    Integer = expected;

    REQUIRE(res == expected);
}

TEST_CASE("Copy constuctor copies values but not slot connections"){
    int res = 0;
    // set value and slot connection
    Property<int> prop1(42);
    prop1.onChange().connect([&](int val) { res += val; });

    // copy
    Property<int> prop2 = prop1;

    // check that prop1 and 2 have the same value
    REQUIRE(prop2 == prop1);
    REQUIRE(prop2 == 42);

    // res doesn't change when
    prop1 = 10;
    REQUIRE(res == 10);
    prop2 = 20;
    REQUIRE(res == 10);
}

TEST_CASE("Check stream operator") {
    int res;
    Property<int> Integer;

    Integer.onChange().connect([&](int val) {
        res = val;
    });

    std::stringstream sstr("42");
    sstr >> Integer;
    REQUIRE(res == 42);
}

TEST_CASE("Check connection among properties") {
    bool res;
    Property<float> InputValue;
    Property<float> OutputValue;
    Property<bool>  CriticalSituation;

    OutputValue.connectFrom(InputValue);

    OutputValue.onChange().connect([&](float val) {
        if (val > 0.5f) CriticalSituation = true;
        else            CriticalSituation = false;
    });

    CriticalSituation.onChange().connect([&](bool val) {
        if (val) res = val;
    });

    InputValue = 0.2;
    REQUIRE_FALSE(res);
    InputValue = 0.4;
    REQUIRE_FALSE(res);
    InputValue = 0.6;
    REQUIRE(res);
}