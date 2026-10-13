#include "pack.h"

int main() { 
    using TestPack = Pack<int, double, char, int>;
    // Task 1: size
    static_assert(TestPack::size == 4);
    static_assert(Pack<>::size == 0);

    // Task 2: index to type
    static_assert(std::is_same_v<TestPack::type<0>, int>);
    static_assert(std::is_same_v<TestPack::type<1>, double>);
    static_assert(std::is_same_v<TestPack::type<2>, char>);
    static_assert(std::is_same_v<TestPack::type<3>, int>);

    // Task 3: type to index
    static_assert(TestPack::index<int> == 0);
    static_assert(TestPack::index<double> == 1);
    static_assert(TestPack::index<char> == 2);
    static_assert(TestPack::index<float> == -1);
    return 0;
}
