#include "searcher.hpp"

bool Searcher::compare(char lhs, char rhs, size_t& char_comparisons)
{
    ++char_comparisons;
    return lhs == rhs;
}

bool Searcher::compareWildcards(char text, char pattern, size_t& char_comparisons, char wildcard)
{
    ++char_comparisons;
    return text == pattern || pattern == wildcard;
}
