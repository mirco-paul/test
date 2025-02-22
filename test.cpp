#include "test.hpp"

int f(int a, int b){
    return a + b;
}

test::TestSuite<f> f_tests(){
    test::TestSuite<f> tests;
    tests.addTest({{2, 2}, 4});
	tests.addTest({{2, 2}, 5});
    return tests;
}

int main(){
    FunctionTraits<decltype(f)>::ReturnType a;
    auto tests = f_tests();
    tests.run();
}
