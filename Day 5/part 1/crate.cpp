#include "crate.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& is, Crate& crate)
{
    for (std::size_t idx = 0; idx < sizeof(crate.data) - 1; ++idx)
    {
        crate.data[idx] = is.get();
    }

    crate.identifier = crate.data[1];

    return is;
}

std::ostream& operator<<(std::ostream& os, const Crate& crate)
{
    return os << crate.data;
}

// 3*num_stacks + num_stacks-1
// read in one crate, skip one whitespace, read another. assert that num_stacks
// crates have been read in

void read_crates_from_line(std::string_view line, std::vector<Stack>& stacks,
                           std::size_t num_stacks)
{
    std::stringstream line_stream(line.data());

    std::size_t count = 0;
    for (Crate crate; auto& stack : stacks)
    {
        [[maybe_unused]] char space_holder;
        line_stream >> crate;
        space_holder = line_stream.get();
        stack.push_back(crate);
        ++count;
    }

    assert(count == num_stacks && "no. of crates read less than no. of stacks");
}

void move_crate(int from_stack, int to_stack, std::vector<Stack>& stacks)
{
    Stack& To_stack = stacks.at(to_stack - 1);
    Stack& From_stack = stacks.at(from_stack - 1);

    auto insert_at_index = std::distance(
        std::find_if(To_stack.begin(), To_stack.end(),
                     [](const Crate& crate) { return !crate.is_empty(); }),
        std::end(To_stack));

    std::ranges::reverse(To_stack.begin(), To_stack.end());

    auto crate_to_move =
        std::find_if(From_stack.begin(), From_stack.end(),
                     [](const Crate& crate) { return !crate.is_empty(); });

    if (insert_at_index == To_stack.size())
        To_stack.push_back(std::move(*crate_to_move));
    else
        To_stack.at(insert_at_index) = std::move(*crate_to_move);

    std::ranges::reverse(To_stack.begin(), To_stack.end());

    From_stack.erase(crate_to_move);
}

void move_crates(int how_many, int from_stack, int to_stack,
                 std::vector<Stack>& stacks)
{
    for (int count = 0; count < how_many; ++count)
    {
        move_crate(from_stack, to_stack, stacks);
    }
}