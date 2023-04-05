#include "tester.hpp"

#include "searcher/naive_searcher.hpp"

#include "text_generator/uniform_text_generator.hpp"

#include "util.hpp"
#include <chrono>
#include <fstream>
#include <ios>
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
        const auto start = std::chrono::high_resolution_clock::now();
        searcher->search(text, pattern, test_result.char_comparisons);
        const auto end = std::chrono::high_resolution_clock::now();

        test_result.duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }

    test_result.duration /= _test_repeat_count;
    test_result.char_comparisons = static_cast<size_t>(1.0 * test_result.char_comparisons / _test_repeat_count);

    return test_result;
}

void Tester::runTests(const std::string& output_filename)
{
    std::ofstream output_file { output_filename, std::ios_base::out | std::ios_base::trunc };
    if (!output_file.is_open()) {
        std::cout << "[Error] Failed to open output file!\n";
        return;
    }

    // Prepare .csv header.
    output_file << "text_generator;text_length;wildcards;pattern_length;searcher;"
                << "test_result_duration_nano;test_result_char_comparisons\n";

    size_t current_test_number = 0;

    for (const auto& text_generator : _text_generators) {
        for (const auto text_length : { 10000, 100000 }) {
            const auto text = text_generator->generate(text_length);
            for (const auto max_wildcard_count : { 0, 4 }) {
                for (size_t pattern_length = 100; pattern_length <= 3000; pattern_length += 100) {
                    const auto pattern = getRandomPattern(text, pattern_length, max_wildcard_count);
                    for (const auto& searcher : _searchers) {
                        std::cout << "Test #" << ++current_test_number << '\t'
                                  << "Text: [generator=" << text_generator->name()
                                  << ", length=" << text_length << " + "
                                  << searcher->name() << " searcher + "
                                  << "Pattern: [wildcards=" << static_cast<bool>(max_wildcard_count)
                                  << ", length=" << pattern_length
                                  << '\n';

                        const auto test_result = runTest(searcher, text, pattern);
                        output_file << text_generator->name() << ';'
                                    << text_length << ';'
                                    << static_cast<bool>(max_wildcard_count) << ';'
                                    << pattern_length << ';'
                                    << searcher->name() << ';'
                                    << test_result.duration.count() << ';'
                                    << test_result.char_comparisons
                                    << '\n';

                        std::cout << "\t\t\t---> Result: "
                                  << test_result.duration.count()
                                  << "ns, char comparisons: "
                                  << test_result.char_comparisons
                                  << '\n';
                    }
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
