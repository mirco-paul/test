#include "test.hpp"

int f(int a, int b){
    return a + b;
}

bool gt5(int a){
    return a > 5;
}

test::TestSuite<f> f_tests(){
    test::TestSuite<f> tests("f tests");
    tests.addTest({{3, 3}, gt5});
    tests.addComparativeTest({{2, 2}, 4});
	//tests.addComparativeTest({{2, 2}, 5});
    return tests;
}

double g(double a, double b, double c){
    return a * b / c;
}

bool custom_comparison(double a, double b){
    return abs(a - b) < 1e-6;
}

test::TestSuite<g> g_tests(){
    test::TestSuite<g> tests("g tests");
    tests.addComparativeTest({{1.0, 2.0, 3.0}, 0.66666667, custom_comparison});
    tests.addComparativeTest({{1.0, 2.0, 3.0}, 0.66666667, test::epsilon_comparison(1e-6)});
    return tests;
}

int main(){
    FunctionTraits<decltype(f)>::ReturnType a;
    auto f_test_suite = f_tests();
    f_test_suite.run();
    auto g_test_suite = g_tests();
    g_test_suite.run();
}
