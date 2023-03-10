#include "crate.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <thread>
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

void print_current_state(std::vector<Stack> stacks, std::size_t max_stack_size)
{
    std::for_each(stacks.begin(), stacks.end(), [=](Stack& stack) {
        std::ranges::reverse(stack.begin(), stack.end());
        stack.resize(max_stack_size);
        std::ranges::reverse(stack.begin(), stack.end());
    });

    for (std::size_t idx = 0; idx < max_stack_size; ++idx)
    {
        for (const auto& stack : stacks)
        {
            if (idx > stack.size() - 1)
                std::cout << Crate();
            else
                std::cout << stack[idx];

            std::cout << ' ';
        }
        std::cout << '\n';
    }

    std::cout << ' ';
    for (std::size_t count = 1; count <= stacks.size(); ++count)
    {
        std::cout << count << Crate();
    }
    std::cout << '\n';
}

std::size_t find_max_stack_size(const std::vector<Stack>& stacks)
{
    std::size_t max_size_ = 0;
    for (const auto& stack : stacks)
    {
        max_size_ = std::max(max_size_, stack.size());
    }
    return max_size_;
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

    print_current_state(stacks, find_max_stack_size(stacks));

    while (std::getline(file, line))
    {
        system("clear");
        std::cout << line << '\n';

        auto instruction = parse_instructions(line);

        move_crates(instruction.how_many, instruction.from_, instruction.to_,
                    stacks);

        print_current_state(stacks, find_max_stack_size(stacks));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // print the top of the all the stacks
    for (const auto& stack : stacks)
    {
        std::cout << *std::find_if(
            stack.begin(), stack.end(),
            [](const Crate& crate) { return !crate.is_empty(); });
    }

    return 0;
}