namespace test{

    template <typename T>
    std::function<bool(const T&, const T&)> epsilon_comparison(const T& epsilon){
        return [epsilon](const T& a, const T& b){
            return abs(a - b) < epsilon;
        };
    }
    
    template<auto functionToTest>
    void UnitTest<functionToTest>::consoleLog(const ReturnType& result, bool passed) const {
        std::cout << (passed ? "Passed" : "Failed") << std::endl;
        if(!passed){
            std::cout << "Operands:" << std::endl;
            // std::cout << operands_ << std::endl;
            std::cout << "Result:" << std::endl;
            std::cout << result << std::endl;
        }
    }

    template<auto functionToTest>
    UnitTest<functionToTest>::UnitTest(ParameterTypes operands,
        std::function<bool(const ReturnType&)> check) : operands_(operands), check_(check){};

    template<auto functionToTest>
    bool UnitTest<functionToTest>::run() const {
        ReturnType result = std::apply(functionToTest, operands_);
        bool passed = check_(result);
        consoleLog(result, passed);
        return passed;
    }

    template<auto functionToTest>
    ComparativeUnitTest<functionToTest>::ComparativeUnitTest(ParameterTypes operands, ReturnType correct_result, 
        std::function<bool(const ReturnType&, const ReturnType&)> comparison) : correct_result_(correct_result),
        UnitTest<functionToTest>::UnitTest(operands, [comparison, correct_result](const ReturnType& result){ return comparison(result, correct_result);}){};

    template<auto functionToTest>
    TestSuite<functionToTest>::TestSuite(std::string suite_name) : suite_name_(suite_name){};

    template<auto functionToTest>
    void TestSuite<functionToTest>::addTest(UnitTest<functionToTest> unit_test) {
        unit_tests_.push_back(unit_test);
    };

    template<auto functionToTest>
    void TestSuite<functionToTest>::addComparativeTest(ComparativeUnitTest<functionToTest> unit_test) {
        unit_tests_.push_back(unit_test);
    };

    template<auto functionToTest>
    void TestSuite<functionToTest>::run() const {
        std::cout << "------------ " << suite_name_ << " ------------" << std::endl;
        for(const UnitTest<functionToTest>& test : unit_tests_){
            if(!test.run()) assert(0);
        }
    }

}   // namespace test
