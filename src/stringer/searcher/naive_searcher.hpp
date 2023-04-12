#pragma once

#include "searcher.hpp"

class NaiveSearcher : public Searcher {
public:
    virtual ~NaiveSearcher() = default;
    virtual Indices search(const std::string& text, const std::string& pattern, size_t& char_comparisons) override;
    virtual Indices searchWildcards(const std::string& text, const std::string& pattern, size_t& char_comparisons, char wildcard) override;
    virtual const char* name() const override;
};
