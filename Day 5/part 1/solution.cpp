#include "crate.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void seek_to_begin(std::istream& is)
{
    is.clear();
    is.seekg(0, std::ios::beg);
}

struct stack_info
{
    std::size_t size;
    std::int_fast32_t num_stacks;
};

stack_info get_stack_info(std::istream& is)
{
    std::size_t stack_size = 0;
    std::string buf;
    for (; std::getline(is, buf) && !std::isdigit(buf.at(1)); ++stack_size)
        ;

    std::int_fast32_t num_stacks;

    // the first number from the end of the line is the largest
    num_stacks = *std::find_if(buf.rbegin(), buf.rend(), [](const char ch) {
        return std::isdigit(ch);
    }) - '0';

    seek_to_begin(is);

    return {stack_size, num_stacks};
}

struct Instruction
{
    int how_many{};
    int from_{};
    int to_{};
};

Instruction parse_instructions(std::string_view line)
{
    Instruction result;

    std::string temp;
    std::stringstream ss(line.data());

    ss >> temp >> result.how_many >> temp >> result.from_ >> temp >> result.to_;
    return result;
}

int main()
{
    std::fstream file("input.txt");

    const auto stack_info = get_stack_info(file);
    const auto initial_stack_size_max = stack_info.size;
    const auto num_stacks = stack_info.num_stacks;

    std::vector<Stack> stacks(num_stacks);

    for (std::size_t count = 0; count < initial_stack_size_max; ++count)
    {
        std::string line;
        std::getline(file, line);
        read_crates_from_line(line, stacks, num_stacks);
    }
    std::string line;
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line))
    {
        auto instruction = parse_instructions(line);

        move_crates(instruction.how_many, instruction.from_, instruction.to_,
                    stacks);
    }

    for (const auto& stack : stacks)
    {
        std::cout << *std::find_if(
            stack.begin(), stack.end(),
            [](const Crate& crate) { return !crate.is_empty(); });
    }

    return 0;
}