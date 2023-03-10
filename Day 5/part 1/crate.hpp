#pragma once

#include <iostream>
#include <string_view>
#include <vector>

struct Crate
{
    char data[4];
    char identifier;

    Crate() : data{"   "}, identifier{' '} {}

    constexpr bool is_empty() const { return identifier == ' '; }
    constexpr bool operator==(const Crate& rhs) const
    {
        return identifier == rhs.identifier;
    }
};

std::istream& operator>>(std::istream& is, Crate& crate);
std::ostream& operator<<(std::ostream& os, const Crate& crate);

using Stack = std::vector<Crate>;

void read_crates_from_line(std::string_view line, std::vector<Stack>& stacks,
                           std::size_t num_stacks);

void move_crate(int from_stack, int to_stack, std::vector<Stack>& stacks);

void move_crates(int how_many, int from_stack, int to_stack,
                 std::vector<Stack>& stacks);