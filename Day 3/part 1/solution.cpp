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

char shared_item(std::string_view lhs_, std::string_view rhs_)
{
    // find duplicates in left and right part of 'backpack'
    for (const auto left_element : lhs_)
    {
        const auto found = std::find(rhs_.begin(), rhs_.end(), left_element);
        if (found != rhs_.end())
            return *found;
    }

    return none_shared;
}

} // namespace solution

int main()
{
    const char* const fname = "input.txt";
    std::fstream file{fname};

    std::string line;
    int total_priority_value{0};

    while (file >> line)
    {
        const std::string_view line_v{line};
        const auto left_ = line_v.substr(0, line_v.size() / 2);
        const auto right_ = line_v.substr(line_v.size() / 2);

        const auto shared_ = solution::shared_item(left_, right_);
        if (shared_ != solution::none_shared)
            total_priority_value += solution::get_priority(shared_);
    }

    std::cout << total_priority_value << '\n';

    return 0;
}