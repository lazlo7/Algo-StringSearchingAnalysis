#pragma once

#include <string>

class TextGenerator {
public:
    virtual ~TextGenerator() = default;
    virtual std::string generate(size_t length) = 0;
};
