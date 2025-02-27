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
#include <functional>
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
    std::function<bool(const T&, const T&)> epsilon_comparison(const T& epsilon);
    
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

        ParameterTypes operands_; /** Test operands. */

        std::function<bool(const ReturnType&)> check_; /** Check if computed result is correct. */

        UnitTest(ParameterTypes operands, std::function<bool(const ReturnType&)> check);

        /**
         * @todo How should we handle logging? Could use flag (e.g. via Makefile) or argument.
         */
        void consoleLog(const ReturnType& result, bool passed) const;

        /**
         * 
         * Runs the unit test, i.e. computes check_(FunctionToTest(operands)).
         * 
         * @return check_(FunctionToTest(operands))
         * 
         */
        bool run() const;
    };

    /**
     * @struct ComparativeUnitTest
     * 
     * Structure for comparison-based unit tests.
     * 
     */
    template<auto functionToTest>
    struct ComparativeUnitTest : UnitTest<functionToTest>{

        /**
         * Get types.
         */
        using ReturnType = typename FunctionTraits<decltype(functionToTest)>::ReturnType;
        using ParameterTypes = typename FunctionTraits<decltype(functionToTest)>::ParameterTypes;

        ReturnType correct_result_; /** Correct test result. */

        // TODO: support check function without correct_result_ (e.g. derive comparison based unit tests from generic check)
        // std::function<bool(const ReturnType&, const ReturnType&)> comparison_; /** Comparison function (computed_result, correct_result) --> bool */

        ComparativeUnitTest(ParameterTypes operands, ReturnType correct_result, std::function<bool(const ReturnType&, const ReturnType&)> comparison = [](const ReturnType& a, const ReturnType& b){ return a == b;});

        /**
         * 
         * Runs the unit test, i.e. computes comparison_(FunctionToTest(operands), correct_result_).
         * 
         * @todo How should we handle logging? Could use flag (e.g. via Makefile) or argument
         * 
         * @return comparison_(FunctionToTest(operands), correct_result_)
         * 
         */
        using UnitTest<functionToTest>::run;
    };

    /**
     * @brief Test suite for FunctionToTest.
     * 
     * @tparam FunctionToTest Function to test.
     * 
     */
    template<auto functionToTest>
    struct TestSuite {

        /**
         * Get types.
         */
        using ReturnType = typename FunctionTraits<decltype(functionToTest)>::ReturnType;
        using ParameterTypes = typename FunctionTraits<decltype(functionToTest)>::ParameterTypes;

        std::string suite_name_;

        std::vector<UnitTest<functionToTest>> unit_tests_;

        TestSuite(std::string suite_name = "Test Suite");

        /**
         * 
         * Adds a unit test to the test suite.
         * 
         */
        void addTest(UnitTest<functionToTest> unit_test);
        
        /**
         * 
         * Adds a comparative unit test to the test suite.
         * 
         */
        void addComparativeTest(ComparativeUnitTest<functionToTest> unit_test);

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
