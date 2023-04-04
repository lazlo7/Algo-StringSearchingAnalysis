#include "tester.hpp"

#include "searcher/naive_searcher.hpp"

#include "text_generator/uniform_text_generator.hpp"

#include "util.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

Tester::Tester(size_t test_repeat_count)
    : _test_repeat_count(test_repeat_count)
{
    _searchers.push_back(std::make_shared<NaiveSearcher>());
    _text_generators.push_back(std::make_shared<DNATextGenerator>());
}

Tester::TestResult Tester::runTest(
    const std::shared_ptr<Searcher>& searcher,
    const std::string& text,
    const std::string& pattern)
{
    TestResult test_result;

    for (size_t i = 0; i < _test_repeat_count; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        searcher->search(text, pattern, test_result.char_comparisons);
        auto end = std::chrono::high_resolution_clock::now();

        test_result.duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }

    test_result.duration /= _test_repeat_count;
    test_result.char_comparisons /= _test_repeat_count;

    return test_result;
}

void Tester::runTests(const std::string& output_filename)
{
    std::ofstream output_file { output_filename };
    if (!output_file.is_open()) {
        std::cout << "[Error] Failed to open output file!\n";
        return;
    }

    for (const auto& text_generator : _text_generators) {
        for (const auto text_length : { 10000, 100000 }) {
            const auto text = text_generator->generate(text_length);
            for (const auto max_wildcard_count : { 0, 4 }) {
                for (size_t pattern_length = 100; pattern_length <= 3000; pattern_length += 100) {
                    const auto pattern = getRandomPattern(text, pattern_length, max_wildcard_count);
                    std::cout << pattern << '\n';
                }
            }
        }
    }

    output_file.close();
}

/*
Pattern length must be greater or equal to max wildcard count.
Text length must be greater or equal to pattern length.
*/
std::string Tester::getRandomPattern(
    const std::string& text,
    size_t pattern_length,
    size_t max_wildcard_count)
{
    if (pattern_length < max_wildcard_count) {
        throw std::invalid_argument("Pattern length must be greater or equal to max wildcard count!");
    }

    if (text.size() < pattern_length) {
        throw std::invalid_argument("Text length must be greater or equal to pattern length!");
    }

    const auto wildcard_count = max_wildcard_count == 0
        ? 0
        : util::getRandomNumber(static_cast<size_t>(1), max_wildcard_count);
    const auto excerpt_length = pattern_length - wildcard_count;
    const auto pattern_index = util::getRandomNumber(static_cast<size_t>(0), text.size() - excerpt_length);

    std::string pattern = text.substr(pattern_index, excerpt_length);
    pattern.reserve(pattern.size() + wildcard_count);

    for (size_t i = 0; i < wildcard_count; ++i) {
        pattern.insert(pattern.begin() + util::getRandomNumber(static_cast<size_t>(0), pattern.size()), '?');
    }

    return pattern;
}
