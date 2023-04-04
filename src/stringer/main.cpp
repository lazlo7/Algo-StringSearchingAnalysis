#include "tester.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: ./stringer <output_filename> [<test_repeat_count>]" << '\n';
        return 1;
    }

    const char* output_filename = argv[1];

    size_t test_repeat_count = 100;
    if (argc >= 3) {
        try {
            test_repeat_count = std::stoull(argv[2]);
        } catch (const std::invalid_argument& e) {
            std::cout << "[Error] Invalid test_repeat_count: must be a positive integer!\n";
            return 1;
        } catch (const std::out_of_range& e) {
            std::cout << "[Error] Invalid test_repeat_count: provided value is too large!\n";
            return 1;
        }
    }

    Tester tester { test_repeat_count };
    tester.runTests(output_filename);

    return 0;
}