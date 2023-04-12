#include "../../src/stringer/searcher/kmp_searcher.hpp"
#include "../../src/stringer/searcher/naive_searcher.hpp"
#include "../../src/stringer/searcher/searcher.hpp"

#include <iostream>
#include <memory>

void test(const std::shared_ptr<Searcher>& searcher, const std::string& text, const std::string& pattern)
{
    std::cout << "Searcher: " << searcher->name() << '\n';

    size_t char_comparisons {};
    const auto result = searcher->searchWildcards(text, pattern, char_comparisons, '?');
    
    std::cout << "Char comparisons: " << char_comparisons << '\n';
    for (const auto index : result) {
        std::cout << index << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::string text;
    std::cin >> text;

    std::string pattern;
    std::cin >> pattern;

    test(std::make_shared<NaiveSearcher>(), text, pattern);
    test(std::make_shared<KMPSearcher>(), text, pattern);
    test(std::make_shared<KMPPreciseBordersSearcher>(), text, pattern);

    return 0;
}