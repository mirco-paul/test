// Print first operand and recurse on the rest
template<typename T, typename... Args>
void rec(std::ostream& os, size_t operand_idx, const T& first, const Args&... rest) {
    os << "Operand " << operand_idx << ":\n" << first;
    if constexpr (sizeof...(rest) > 0) {
        os << std::endl;
        rec(os, operand_idx + 1, rest...);
    }
}

// Overload << operator for std::tuple
template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tup) {
    std::apply([&os](const auto&... args) { rec(os, 0, args...); }, tup);
    return os;
}

// Generic << operator for iterable types other than strings
template<typename T>
requires (std::ranges::range<T> && !std::same_as<T, std::string> && !is_c_string<T>)
std::ostream& operator<<(std::ostream& os, const T& container) {
    os << "[";
    bool first = true;
    for (const auto& item : container) {
        if (!first) os << ", ";
        os << item;
        first = false;
    }
    os << "]";
    return os;
}