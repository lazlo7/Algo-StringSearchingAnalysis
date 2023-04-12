#include "../../src/stringer/searcher/kmp_searcher.hpp"
#include <iostream>

int main()
{
    std::string pattern;
    std::cin >> pattern;

    size_t char_comparisons = 0;
    const auto substrings = KMPSearcher::splitByWildcard(pattern, '?', char_comparisons);

    std::cout << "Result:\n";
    for (const auto& [substring, substring_index] : substrings) {
        std::cout << substring << ' ' << substring_index << '\n';
    }

    std::cout << "Char comparisons: " << char_comparisons << '\n';

    return 0;
}
