#include "naive_searcher.hpp"

Searcher::Indices NaiveSearcher::search(
    const std::string& text,
    const std::string& pattern,
    size_t& char_comparisons)
{
    Searcher::Indices indices;

    for (size_t text_index = 0; text_index < text.size(); ++text_index) {
        bool found = true;

        for (size_t pattern_index = 0; pattern_index < pattern.size(); ++pattern_index) {
            if (text_index + pattern_index >= text.size()
                || !compare(text[text_index + pattern_index], pattern[pattern_index], char_comparisons)) {
                found = false;
                break;
            }
        }

        if (found) {
            indices.push_back(text_index);
        }
    }

    return indices;
}

const char* NaiveSearcher::name() const
{
    return "Naive";
}
