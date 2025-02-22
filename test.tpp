namespace test{
    
    template<typename T>
    void consoleLog(const T& result, const T& correct){
        bool passed = result == correct;
        std::cout << (passed ? "Passed" : "Failed") << std::endl;
        if(!passed){
            std::cout << "Result:" << std::endl;
            std::cout << result << std::endl;
            std::cout << "Correct:" << std::endl;
            std::cout << correct << std::endl;
        }
    }

    template<auto functionToTest>
    UnitTest<functionToTest>::UnitTest(ParameterTypes operands, ReturnType correct_result) : operands(operands), correct_result(correct_result) {};

    template<auto functionToTest>
    bool UnitTest<functionToTest>::run() const {
        ReturnType result = std::apply(functionToTest, operands);
        consoleLog(result, correct_result);
        return result == correct_result;
    }

    template<auto functionToTest>
    TestSuite<functionToTest>::TestSuite() {};

    template<auto functionToTest>
    void TestSuite<functionToTest>::addTest(UnitTest<functionToTest> unit_test) {
        unit_tests.push_back(unit_test);
    };

    template<auto functionToTest>
    void TestSuite<functionToTest>::run() const {
        for(const UnitTest<functionToTest>& test : unit_tests){
            if(!test.run()) assert(0);
        }
    }

}   // namespace test
