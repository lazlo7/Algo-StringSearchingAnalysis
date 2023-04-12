#include "kmp_searcher.hpp"
#include "searcher.hpp"
#include <cstddef>

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

/*
Splits pattern by a wildcard character into substrings.
Returns a vector of pairs (substring, substring's starting index in pattern).
*/
std::vector<std::pair<std::string, size_t>> KMPSearcher::splitByWildcard(
    const std::string& pattern,
    char wildcard,
    size_t& char_comparisons)
{
    std::vector<std::pair<std::string, size_t>> non_wildcard_substrings;
    size_t first_non_wildcard_index = 0;
    bool first_non_wildcard_found = false;

    for (size_t i = 0; i < pattern.size(); ++i) {
        if (compare(pattern[i], wildcard, char_comparisons)) {
            if (first_non_wildcard_found) {
                non_wildcard_substrings.push_back(std::make_pair(
                    pattern.substr(first_non_wildcard_index, i - first_non_wildcard_index),
                    first_non_wildcard_index));
                first_non_wildcard_found = false;
            }
            continue;
        }

        if (!first_non_wildcard_found) {
            first_non_wildcard_index = i;
            first_non_wildcard_found = true;
        }
    }

    if (first_non_wildcard_found) {
        non_wildcard_substrings.push_back(std::make_pair(pattern.substr(first_non_wildcard_index), first_non_wildcard_index));
    }

    return non_wildcard_substrings;
}

/*
Inspired by:
https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%90%D1%85%D0%BE-%D0%9A%D0%BE%D1%80%D0%B0%D1%81%D0%B8%D0%BA
*/
Searcher::Indices KMPSearcher::searchWildcards(
    const std::string& text,
    const std::string& pattern,
    size_t& char_comparisons,
    char wildcard)
{
    const auto non_wildcard_substrings = splitByWildcard(pattern, wildcard, char_comparisons);

    Indices text_encounters(text.size());
    for (const auto& [substring, substring_index] : non_wildcard_substrings) {
        const auto substring_indices = search(text, substring, char_comparisons);
        for (const auto substring_index_in_text : substring_indices) {
            if (substring_index_in_text >= substring_index) {
                ++text_encounters[substring_index_in_text - substring_index];
            }
        }
    }

    Indices indices;
    for (size_t i = 0; i + pattern.length() < text_encounters.size() + 1; ++i) {
        if (text_encounters[i] == non_wildcard_substrings.size()) {
            indices.push_back(i);
        }
    }

    return indices;
}

Searcher::Indices KMPPreciseBordersSearcher::searchWildcards(
    const std::string& text,
    const std::string& pattern,
    size_t& char_comparisons,
    char wildcard)
{
    const auto non_wildcard_substrings = KMPSearcher::splitByWildcard(pattern, wildcard, char_comparisons);

    Indices text_encounters(text.size());
    for (const auto& [substring, substring_index] : non_wildcard_substrings) {
        const auto substring_indices = search(text, substring, char_comparisons);
        for (const auto substring_index_in_text : substring_indices) {
            if (substring_index_in_text >= substring_index) {
                ++text_encounters[substring_index_in_text - substring_index];
            }
        }
    }

    Indices indices;
    for (size_t i = 0; i + pattern.length() < text_encounters.size() + 1; ++i) {
        if (text_encounters[i] == non_wildcard_substrings.size()) {
            indices.push_back(i);
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
