#pragma once

#include "text_generator.hpp"
#include <random>

class UniformTextGenerator : public TextGenerator {
public:
    UniformTextGenerator(const std::string& alphabet);
    ~UniformTextGenerator() = default;
    virtual std::string generate(size_t length) override;

protected:
    std::string _alphabet;
    std::mt19937 _random_generator;
    std::uniform_int_distribution<size_t> _random_distribution;
};

class DNATextGenerator : public UniformTextGenerator {
public:
    DNATextGenerator();
    ~DNATextGenerator() = default;
    virtual const char* name() const override;
};

class BinaryTextGenerator : public UniformTextGenerator {
public:
    BinaryTextGenerator();
    ~BinaryTextGenerator() = default;
    virtual const char* name() const override;
};
