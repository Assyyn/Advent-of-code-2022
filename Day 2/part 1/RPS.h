#ifndef RPS_H
#define RPS_H

// AX BY CZ ~ 1 2 3
// W D L    ~ 6 3 0

// Task 1:  I feed character, it gib value ..done~
// Task 2:  I gib two value, it gib who won

#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

namespace rps
{
enum Symbol
{
    rock = 1,
    paper,
    scissors,
};

constinit std::array<std::pair<char, char>, 3> rpsValues{
    {{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}}};

constexpr int static value(const char ch)
{
    for (int index{1}; const auto& [key1, key2] : rpsValues)
    {
        if (ch == key1 || ch == key2)
            return index;

        ++index;
    }

    return 0;
}

constexpr int static compare(const int p1, const int p2)
{
    if (p1 < rock || p1 > scissors || p2 < rock || p2 > scissors)
        return -1;

    if (p1 == p2) // draw
        return 3;

    if (p1 == (p2 + 1)) // if the difference is only one, and p1>p2 p1 wins
        return 6;

    if (p1 == rock && p2 == scissors)
        return 6;

    return 0;
}

[[nodiscard]] constexpr static std::pair<int, int> calculate_scores(char p1,
                                                                    char p2)
{
    int p1_s{0}, p2_s{0};

    int p1_raw{rps::value(p1)};
    int p2_raw{rps::value(p2)};

    // add raw scores
    p1_s += p1_raw;
    p2_s += p2_raw;

    // compare and add appropriate scores
    p1_s += rps::compare(p1_raw, p2_raw);
    p2_s += rps::compare(p2_raw, p1_raw);

    // return scores
    return {p1_s, p2_s};
}
} // namespace rps

#endif