#include "searcher.hpp"

bool Searcher::compare(char lhs, char rhs, size_t& char_comparisons)
{
    ++char_comparisons;
    return lhs == rhs;
}
