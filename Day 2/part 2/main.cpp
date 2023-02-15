#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <utility>

// Problem Statement:
/*  'X' = lose, 'Y' = draw, 'Z' = win
 *  'A' = rock , 'B' = paper, 'C' = scissors
 */

namespace rps
{

enum class Sign
{
    rock = 1,
    paper = 2,
    scissors = 3,

    invalid_ = -1,
};

enum class Result
{
    LOSE = 0,
    DRAW = 3,
    WIN = 6,

    invalid_ = -1,
};

constinit std::array rps_values_{'A', 'B', 'C'};
constinit std::array result_values_{'X', 'Y', 'Z'};

// returns a Sign object from given character, 'A' to 'C' otherwise returns an
// invalid object
constexpr Sign get_rps_value(char sign_)
{
    const auto found = std::find(rps_values_.begin(), rps_values_.end(), sign_);
    if (found == rps_values_.end())
        return Sign::invalid_;

    return static_cast<Sign>(found - rps_values_.begin() + 1);
}

// returns a Result object from given character, 'X' to 'Z' otherwise returns an
// invalid object
constexpr Result get_result_value(char sign_)
{
    const auto found = std::find(result_values_.begin(), result_values_.end(),
                                 sign_);
    if (found == result_values_.end())
        return Result::invalid_;

    return static_cast<Result>((found - result_values_.begin()) * 3);
}

// deduces the sign to be used depending on the expected result and expected
// opponent sign
constexpr Sign deduce_sign(Sign sign, Result expected_)
{
    switch (expected_)
    {
    case Result::DRAW:
        return sign;

    case Result::WIN:
        if (sign == Sign::scissors)
            return Sign::rock;

        return (Sign)((int)sign + 1);

    case Result::LOSE:
        if (sign == Sign::rock)
            return Sign::scissors;

        return (Sign)((int)sign - 1);

        // GIGO
    case Result::invalid_:
        return Sign::invalid_;
    }
}

// returns scores for both players p1 and p2 respectively. expected_result is
// for player 2; if it is WIN, player 2 should win etc
constexpr std ::pair<int, int> calculate_score(char p1_sign,
                                               char expected_result)
{
    const Sign p2_sign = deduce_sign(get_rps_value(p1_sign),
                                     get_result_value(expected_result));

    const int p1_score = int(p1_sign) + static_cast<int>(Result::WIN) -
                         int(get_result_value(expected_result));
    const int p2_score = int(p2_sign) + int(get_result_value(expected_result));

    return {p1_score, p2_score};
}

} // namespace rps

int main()
{
    const auto filename_ = "input.txt";
    std::fstream file{filename_};
    if (!file)
    {
        std::cerr << "Could not open file!";
        return -1;
    }

    char given_sign{};
    char expected_result{};

    int p1_score{0};
    int p2_score{0};

    while (file >> given_sign >> expected_result)
    {
        const auto scores = rps::calculate_score(given_sign, expected_result);
        p1_score += scores.first;
        p2_score += scores.second;
    }

    std::cout << "Player 1 score: " << p1_score << '\n'
              << "Player 2 score: " << p2_score << '\n';

    return 0;
}