#pragma once

#include <string>
#include <vector>

class Searcher {
public:
    using Indices = std::vector<size_t>;
    virtual ~Searcher() = default;
    virtual Indices search(const std::string& text, const std::string& pattern, size_t& char_comparisons) = 0;
};
