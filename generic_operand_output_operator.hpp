#include <iostream>
#include <tuple>

// Print first operand and recurse on the rest
template<typename T, typename... Args>
void rec(std::ostream& os, size_t operand_idx, const T& first, const Args&... rest);

// Overload << operator for std::tuple
template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tup);

#include "generic_operand_output_operator.tpp"