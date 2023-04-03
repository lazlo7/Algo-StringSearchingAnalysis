#include "uniform_text_generator.hpp"

#include <stdexcept>

UniformTextGenerator::UniformTextGenerator(const std::string& alphabet)
    : _alphabet(alphabet)
    , _random_generator(std::random_device()())
    , _random_distribution(0, alphabet.size() - 1)
{
    if (alphabet.empty()) {
        throw std::invalid_argument("Alphabet can't be empty!");
    }
}

std::string UniformTextGenerator::generate(size_t length)
{
    std::string result;
    result.resize(length);

    for (size_t i = 0; i < length; ++i) {
        result[i] = _alphabet[_random_distribution(_random_generator)];
    }

    return result;
}

DNATextGenerator::DNATextGenerator()
    : UniformTextGenerator("ACGT")
{
}

const char* DNATextGenerator::name() const
{
    return "DNA";
}
