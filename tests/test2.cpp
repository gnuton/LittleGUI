#include "../third_party/catch2/catch.hpp"

int Factorial2( int number ) {
    printf("TESTTTT");
    return number <= 1 ? number : Factorial2( number - 1 ) * number;  // fail
    //return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "222 Factorial of 0 is 1 (fail)", "[single-file]" ) {
REQUIRE( Factorial2(0) == 1 );
}

TEST_CASE( "222 Factorials of 1 and higher are computed (pass)", "[single-file]" ) {
REQUIRE( Factorial2(1) == 1 );
REQUIRE( Factorial2(2) == 2 );
REQUIRE( Factorial2(3) == 6 );
REQUIRE( Factorial2(10) == 3628800 );
}