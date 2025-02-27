#include <iostream>
#include <ranges>
#include <tuple>

// Print first operand and recurse on the rest
template<typename T, typename... Args>
void rec(std::ostream& os, size_t operand_idx, const T& first, const Args&... rest);

// Overload << operator for std::tuple
template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tup);

// Concept to detect C-style strings (both char arrays and const char*)
template<typename T>
concept is_c_string = 
    (std::is_array_v<std::remove_reference_t<T>> && 
    std::same_as<std::remove_extent_t<std::remove_reference_t<T>>, char>) || 
    std::same_as<std::remove_cvref_t<T>, const char*>;

// Generic << operator for iterable types other than strings
template<typename T>
requires (std::ranges::range<T> && !std::same_as<T, std::string> && !is_c_string<T>)
std::ostream& operator<<(std::ostream& os, const T& container);

#include "ostream_operators.tpp"