#include "tester.hpp"

#include <iostream>
#include <sstream>
#include <string>

static size_t parseSizeT(int argc, char** args, const std::string& arg_prefix, size_t default_value)
{
    for (int i = 0; i < argc; ++i) {
        std::string arg { args[i] };
        if (arg.starts_with(arg_prefix)) {
            const std::string to_parse = arg.substr(arg_prefix.size());
            if (to_parse.empty()) {
                return default_value;
            }

            std::stringstream stream_to_parse { to_parse };
            size_t value;
            stream_to_parse >> value;

            if (stream_to_parse.fail()) {
                return default_value;
            }

            return value;
        }
    }

    return default_value;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: ./stringer <output_filename> [-tr=<test_repeat_count>]" << '\n'
                  << "<output_filename> - filename to write results to,\n"
                  << "<test_repeat_count> - how many times each test should be repeated [default = 100]\n";

        return 1;
    }

    const char* output_filename = argv[1];
    const auto test_repeat_count = parseSizeT(argc, argv, "-tr=", 100);

    Tester tester { test_repeat_count };
    tester.runTests(output_filename);

    return 0;
}