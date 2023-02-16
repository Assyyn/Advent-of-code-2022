#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

namespace solution
{
constinit std::array<std::pair<char, int>, 52> priorities_{[] {
    std::array<std::pair<char, int>, 52> temp_;
    char char_{'a'};
    int priority{1};

    for (auto& [character_, priority_] : temp_)
    {
        if (priority == 27)
            char_ = 'A';

        character_ = char_++;
        priority_ = priority++;
    }

    return temp_;
}()};

int get_priority(const char target_)
{
    return std::find_if(
               priorities_.begin(), priorities_.end(),
               [&](const auto& pair_) { return pair_.first == target_; })
        ->second;
}

constinit char none_shared = ' ';

using sv_ = std::string_view;
char find_group_badge(sv_ pack_1, sv_ pack_2, sv_ pack_3)
{
    std::string common_in_first_two;
    for (const char ch : pack_1)
    {
        const auto found = std::find(pack_2.begin(), pack_2.end(), ch);
        if (found != pack_2.end())
            common_in_first_two += *found;
    }

    for (const char ch : common_in_first_two)
    {
        const auto found = std::find(pack_3.begin(), pack_3.end(), ch);
        if (found != pack_3.end())
            return *found;
    }

    return none_shared;
}

} // namespace solution

int main()
{
    std::fstream file{"input.txt"};

    std::string pack_1, pack_2, pack_3;
    int total_priority_value = 0;

    while (file >> pack_1 >> pack_2 >> pack_3)
    {
        const auto badge_type = solution::find_group_badge(pack_1, pack_2,
                                                           pack_3);
        if (badge_type != solution::none_shared)
            total_priority_value += solution::get_priority(badge_type);
    }

    std::cout << total_priority_value << '\n';

    return 0;
}