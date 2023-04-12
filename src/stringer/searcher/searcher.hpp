#pragma once

#include "../nameable.hpp"

#include <string>
#include <vector>

class Searcher : public Nameable {
public:
    using Indices = std::vector<size_t>;
    virtual ~Searcher() = default;
    virtual Indices search(const std::string& text, const std::string& pattern, size_t& char_comparisons) = 0;
    virtual Indices searchWildcards(const std::string& text, const std::string& pattern, size_t& char_comparisons, char wildcard) = 0;

protected:
    static bool compare(char lhs, char rhs, size_t& char_comparisons);
    static bool compareWildcards(char text, char pattern, size_t& char_comparisons, char wildcard);
};
