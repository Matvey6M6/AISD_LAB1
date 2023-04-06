#include "test.hpp"
long long lcg(){
    static long long x = 0;
    x = (1021*x+24631) % 116640;
    return x;
}

int tests()
{
    
    return 1;
}