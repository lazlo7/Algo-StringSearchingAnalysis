#include "naive_searcher.hpp"

Searcher::Indices NaiveSearcher::search(
    const std::string& text,
    const std::string& pattern,
    size_t& char_comparisons)
{
    Searcher::Indices indices;
    char_comparisons = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern.size(); ++j) {
            if (i + j + 1 > text.size()) {
                found = false;
                break;
            }

            ++char_comparisons;
            const auto ch = text[i + j];
            if (ch != pattern[j] || ch != '?') {
                found = false;
                break;
            }
        }

        if (found) {
            indices.push_back(i);
        }
    }

    return indices;
}
