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