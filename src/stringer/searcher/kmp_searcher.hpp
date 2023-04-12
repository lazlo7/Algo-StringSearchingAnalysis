#pragma once

#include "searcher.hpp"

class KMPSearcher : public Searcher {
public:
    virtual ~KMPSearcher() = default;
    virtual Indices search(const std::string& text, const std::string& pattern, size_t& char_comparisons) override;
    virtual Indices searchWildcards(const std::string& text, const std::string& pattern, size_t& char_comparisons, char wildcard) override;
    virtual const char* name() const override;
    static std::vector<std::pair<std::string, size_t>> splitByWildcard(const std::string& pattern, char wildcard, size_t& char_comparisons); 

private:
    static constexpr char kAbsentChar = '#';
};

class KMPPreciseBordersSearcher : public Searcher {
public:
    virtual ~KMPPreciseBordersSearcher() = default;
    virtual Indices search(const std::string& text, const std::string& pattern, size_t& char_comparisons) override;
    virtual Indices searchWildcards(const std::string& text, const std::string& pattern, size_t& char_comparisons, char wildcard) override;
    virtual const char* name() const override;

private:
    static constexpr char kAbsentChar = '#';
};
