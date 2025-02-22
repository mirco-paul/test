/**
 * @file test.hpp
 * 
 * @brief Testing framework.
 * 
 * @author David Gu
 * @author Mirco Paul
 * 
 * @date \today
 */

#pragma once

#include "function_traits.hpp"

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @namespace test
 * 
 * @brief Namespace of the testing framework.
 * 
 */
namespace test{

    template<typename T>
    void consoleLog(const T& result, const T& correct);
    
    /**
     * @struct UnitTest
     * 
     * Structure for unit tests.
     * 
     */
    template<auto functionToTest>
    struct UnitTest {
        /**
         * Get types.
         */
        using ReturnType = typename FunctionTraits<decltype(functionToTest)>::ReturnType;
        using ParameterTypes = typename FunctionTraits<decltype(functionToTest)>::ParameterTypes;

        ParameterTypes operands; /** Test operands. */
        ReturnType correct_result; /** Correct test result. */

        UnitTest(ParameterTypes operands, ReturnType correct_result);

        /**
         * 
         * Runs the unit test, i.e. checks if FunctionToTest(operands) == result.
         * 
         * @todo How should we handle logging? Could use flag (e.g. via Makefile) or argument
         * 
         * @return FunctionToTest(operands) == result
         * 
         */
        bool run() const;
    };

    /**
     * @brief Test suite for FunctionToTest.
     * 
     * @tparam FunctionToTest Function to test.
     * 
     */
    template<auto functionToTest>
    struct TestSuite {

        std::vector<UnitTest<functionToTest>> unit_tests;

        TestSuite();
        
        /**
         * 
         * Adds a unit test to the test suite.
         * 
         */
        void addTest(UnitTest<functionToTest> unit_test);

        /**
         * 
         * Runs the entire test suite. Currently fails after the first wrong test.
         * 
         * @todo Find neat way to let the user determine failure and logging behaviour.
         * 
         */
        void run() const;
    };

} // namespace test

#include "test.tpp"
