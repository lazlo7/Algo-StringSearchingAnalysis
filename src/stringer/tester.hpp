#pragma once

#include "searcher/naive_searcher.hpp"
#include "searcher/searcher.hpp"

#include "text_generator/text_generator.hpp"
#include "text_generator/uniform_text_generator.hpp"

#include <chrono>
#include <memory>
#include <string>
#include <vector>

class Tester {
public:
    struct TestResult {
        std::chrono::nanoseconds duration;
        size_t char_comparisons;
    };

    Tester(size_t test_repeat_count);
    ~Tester() = default;

    void runTests(const std::string& output_filename);
    TestResult runTest(
        const std::shared_ptr<Searcher>& searcher,
        const std::string& text,
        const std::string& pattern);

private:
    static std::string getRandomPattern(
        const std::string& text,
        size_t pattern_length,
        size_t max_wildcard_count);

    std::vector<std::shared_ptr<Searcher>> _searchers;
    std::vector<std::shared_ptr<TextGenerator>> _text_generators;
    size_t _test_repeat_count;
};
