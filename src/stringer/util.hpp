#pragma once

#include <random>

namespace util {
static std::mt19937 _random_generator { std::random_device()() };
static std::uniform_real_distribution<double> _random_real_distribution { 0.0, 1.0 };

template <typename T>
requires std::is_integral_v<T>
T getRandomNumber(T min, T max)
{
    return std::round(_random_real_distribution(_random_generator) * (max - min)) + min;
}
}
