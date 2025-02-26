#include "test.hpp"

int f(int a, int b){
    return a + b;
}

bool gt5(int a){
    return a > 5;
}

test::TestSuite<f> f_tests(){
    test::TestSuite<f> tests;
    tests.addTest({{3, 3}, gt5});
    tests.addComparativeTest({{2, 2}, 4});
	// tests.addComparativeTest({{2, 2}, 5});
    return tests;
}

int main(){
    FunctionTraits<decltype(f)>::ReturnType a;
    auto tests = f_tests();
    tests.run();
}
