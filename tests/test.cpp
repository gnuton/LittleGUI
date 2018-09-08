#define CATCH_CONFIG_NO_POSIX_SIGNALS

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "../third_party/catch2/catch.hpp"

int Factorial( int number ) {
    printf("TESTTTT");
    return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
    //return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "111 Factorial of 0 is 1 (fail)", "[single-file]" ) {
REQUIRE( Factorial(0) == 1 );
}

TEST_CASE( "111 Factorials of 1 and higher are computed (pass)", "[single-file]" ) {
REQUIRE( Factorial(1) == 1 );
REQUIRE( Factorial(2) == 2 );
REQUIRE( Factorial(3) == 6 );
REQUIRE( Factorial(10) == 3628800 );
}