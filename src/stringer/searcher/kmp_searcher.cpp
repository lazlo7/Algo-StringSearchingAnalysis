#include "kmp_searcher.hpp"

Searcher::Indices KMPSearcher::search(const std::string& text, const std::string& pattern, size_t& char_comparisons)
{
    // Compute prefix function.
    Indices prefixes(pattern.size());
    for (size_t i = 1, k = 0; i < pattern.size(); ++i) {
        while (k > 0 && !compare(pattern[i], pattern[k], char_comparisons)) {
            k = prefixes[k - 1];
        }

        if (compare(pattern[i], pattern[k], char_comparisons)) {
            ++k;
        }

        prefixes[i] = k;
    }

    // Compute result using prefix function.
    Indices indices;
    for (size_t i = 0, k = 0; i < text.size(); ++i) {
        while (k > 0 && !compare(pattern[k], text[i], char_comparisons)) {
            k = prefixes[k - 1];
        }

        if (compare(pattern[k], text[i], char_comparisons)) {
            ++k;
        }

        if (k == pattern.size()) {
            indices.push_back(i - pattern.size() + 1);
        }
    }

    return indices;
}

Searcher::Indices KMPPreciseBordersSearcher::search(const std::string& text, const std::string& pattern, size_t& char_comparisons)
{
    // Compute prefix function.
    Indices prefixes(pattern.size());
    for (size_t i = 1, k = 0; i < pattern.size(); ++i) {
        while (k > 0 && !compare(pattern[i], pattern[k], char_comparisons)) {
            k = prefixes[k - 1];
        }

        if (compare(pattern[i], pattern[k], char_comparisons)) {
            ++k;
        }

        prefixes[i] = k;
    }

    // Compute precise prefixes using prefix function.
    Indices precise_prefixes(pattern.size());
    for (size_t i = 1; i + 1 < pattern.size(); ++i) {
        precise_prefixes[i] = compare(pattern[prefixes[i] + 1], pattern[i + 1], char_comparisons)
            ? precise_prefixes[prefixes[i]]
            : prefixes[i];
    }

    precise_prefixes[pattern.size() - 1] = prefixes[pattern.size() - 1];

    // Compute result using precise prefixes.
    Indices indices;
    for (size_t i = 0, k = 0; i < text.size(); ++i) {
        while (k > 0 && !compare(pattern[k], text[i], char_comparisons)) {
            k = precise_prefixes[k - 1];
        }

        if (compare(pattern[k], text[i], char_comparisons)) {
            ++k;
        }

        if (k == pattern.size()) {
            indices.push_back(i - pattern.size() + 1);
        }
    }

    return indices;
}

const char* KMPSearcher::name() const
{
    return "KMP (Standard Borders)";
}

const char* KMPPreciseBordersSearcher::name() const
{
    return "KMP (Precise Borders)";
}
