#include <iostream>
#include "../../src/stringer/searcher/naive_searcher.hpp"

int main() {
    std::string text;
    std::cin >> text;

    std::string pattern;
    std::cin >> pattern;

    NaiveSearcher searcher{};
    size_t char_comparisons{};
    const auto result = searcher.search(text, pattern, char_comparisons);

    std::cout << "Char comparisons: " << char_comparisons << '\n';
    for (const auto index : result) {
        std::cout << index << ' ';
    }
    std::cout << '\n';

    return 0;
}