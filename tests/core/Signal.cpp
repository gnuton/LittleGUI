#include <catch.hpp>
#include <core/Signal.h>

TEST_CASE( "Check connection between signals and slots functions" ) {
    Signal<std::string, int> signal;
    int _arg2;
    std::string _arg1;

    signal.connect([&_arg1, &_arg2](std::string arg1, int arg2) {
        _arg1 = arg1;
        _arg2 = arg2;
    });

    signal.emit("a", 42);

    REQUIRE( _arg1 == "a");
    REQUIRE( _arg2 == 42);
}

TEST_CASE("Check connection between signals and slots methods") {
    class A {
    public:
        std::string _arg1;
        int _arg2;

        void theSlot(std::string a, int b) {
            _arg1 = a;
            _arg2 = b;
        }
    };

    auto a = new A;

    Signal<std::string, int> signal;
    signal.connectMember(a, &A::theSlot);
    signal.emit("a", 42);
    REQUIRE( a->_arg1 == "a");
    REQUIRE( a->_arg2 == 42);
}

TEST_CASE("Check disconnect by id") {
    Signal<std::string, int> signal;
    std::string _arg1, _arg3;
    int _arg2 = 0, _arg4 = 0;

    auto id1 = signal.connect([&_arg1, &_arg2](std::string arg1, int arg2) {
        _arg1 = arg1;
        _arg2 = arg2;
    });
    auto id2 = signal.connect([&_arg3, &_arg4](std::string arg1, int arg2) {
        _arg3 = arg1;
        _arg4 = arg2;
    });
    signal.disconnect(id1);
    signal.emit("a", 42);

    REQUIRE( id1 != id2 );
    REQUIRE( _arg1 == "");
    REQUIRE( _arg2 == 0);
    REQUIRE( _arg3 == "a");
    REQUIRE( _arg4 == 42);
}

TEST_CASE("Check disconnect all slots") {
    Signal<std::string, int> signal;
    std::string _arg1, _arg3;
    int _arg2 = 0, _arg4 = 0;

    auto id1 = signal.connect([&_arg1, &_arg2](std::string arg1, int arg2) {
        _arg1 = arg1;
        _arg2 = arg2;
    });
    auto id2 = signal.connect([&_arg3, &_arg4](std::string arg1, int arg2) {
        _arg3 = arg1;
        _arg4 = arg2;
    });
    signal.disconnectAll();
    signal.emit("a", 42);

    REQUIRE( id1 != id2 );
    REQUIRE( _arg1 == "");
    REQUIRE( _arg2 == 0);
    REQUIRE( _arg3 == "");
    REQUIRE( _arg4 == 0);
}
