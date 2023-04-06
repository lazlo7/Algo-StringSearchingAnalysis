#pragma once

#include "searcher.hpp"

class KMPSearcher : public Searcher {
public:
    virtual ~KMPSearcher() = default;
    virtual Indices search(const std::string& text, const std::string& pattern, size_t& char_comparisons) override;
    virtual const char* name() const override;

private:
    static constexpr char kAbsentChar = '#';

    Indices computePrefixes(const std::string& pattern, size_t& char_comparisons);
};
