#pragma once

#include "../nameable.hpp"

#include <string>

class TextGenerator : public Nameable {
public:
    virtual ~TextGenerator() = default;
    virtual std::string generate(size_t length) = 0;
};
