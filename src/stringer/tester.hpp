#pragma once

#include "searcher/searcher.hpp"
#include "text_generator/text_generator.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

class Tester {
public:
    struct TestResult {
        std::chrono::nanoseconds duration {};
        size_t char_comparisons {};
    };

    Tester();

    void runTests(
        const std::string& output_filename,
        size_t test_repeat_count,
        size_t pattern_repeat_count);
    TestResult runTest(
        const std::shared_ptr<Searcher>& searcher,
        const std::string& text,
        const std::string& pattern,
        bool wildcards,
        size_t test_repeat_count);

private:
    static std::string getRandomPattern(
        const std::string& text,
        size_t pattern_length,
        size_t max_wildcard_count);

    std::vector<std::shared_ptr<Searcher>> _searchers;
    std::vector<std::shared_ptr<TextGenerator>> _text_generators;
};
