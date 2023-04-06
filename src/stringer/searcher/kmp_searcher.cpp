#include "kmp_searcher.hpp"

Searcher::Indices KMPSearcher::computePrefixes(const std::string& pattern, size_t& char_comparisons)
{   
    Indices prefixes(pattern.size());

    for (size_t i = 1; i < pattern.size(); ++i) {
        auto k = prefixes[i - 1];
        while (k > 0 && !compare(pattern[i], pattern[k], char_comparisons)) {
            k = prefixes[k - 1];
        }

        if (compare(pattern[i], pattern[k], char_comparisons)) {
            ++k;
        }

        prefixes[i] = k;
    }

    return prefixes;
}

Searcher::Indices KMPSearcher::search(const std::string& text, const std::string& pattern, size_t& char_comparisons)
{
    const std::string needle = pattern + kAbsentChar + text;
    const auto prefixes = computePrefixes(needle, char_comparisons);
    Indices indices;

    for (size_t i = 0; i < text.size(); ++i) {
        if (prefixes[pattern.size() + i + 1] == pattern.length()) {
            indices.push_back(i - pattern.size());
        }
    }

    return indices;
}

const char* KMPSearcher::name() const
{
    return "KMP (Standard Borders)";
}
