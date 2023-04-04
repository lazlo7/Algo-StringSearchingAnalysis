#include "tester.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include "util.hpp"

Tester::Tester(size_t test_repeat_count)
    : _test_repeat_count(test_repeat_count)
{
    _searchers.push_back(std::make_shared<NaiveSearcher>());
    _text_generators.push_back(std::make_shared<UniformTextGenerator>());
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
        }
    }

    output_file.close();
}

/*
Pattern length must be greater or equal to max wildcard count.
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

    const auto wildcard_count = getRandomNumber(0, max_wildcard_count);
    const auto excerpt_length = pattern_length - wildcard_count;
    const auto pattern_index = getRandomNumber(0, text.size() - excerpt_length);
    std::string pattern = text.substr(pattern_index, excerpt_length); 

    for (size_t i = 0; i < wildcard_count; ++i) {
        pattern += '?';
    }
}
