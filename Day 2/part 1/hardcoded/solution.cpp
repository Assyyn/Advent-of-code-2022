#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

namespace rps
{
static constexpr std::array<std::pair<std::string_view, int>, 9> rpsValues{
    {{"A X", 3},
     {"A Y", 6},
     {"A Z", 0},
     {"B X", 0},
     {"B Y", 3},
     {"B Z", 6},
     {"C X", 6},
     {"C Y", 0},
     {"C Z", 3}}};

[[nodiscard]] constexpr int raw(char symbol)
{
    constexpr std::array symbols{'X', 'Y', 'Z'};

    auto found = std::find(symbols.begin(), symbols.end(), symbol);
    if (!found)
        return -1;

    static constexpr int index_on_one{1};
    return static_cast<int>(index_on_one + found - symbols.begin());
}

[[nodiscard]] constexpr int score(std::string_view line)
{
    auto found = std::find_if(rpsValues.begin(), rpsValues.end(),
                              [=](const auto& pair) {
                                  if (line == pair.first)
                                      return true;
                                  return false;
                              });
    if (found == rpsValues.end())
        return -1;

    return found->second + raw(line.back());
}

} // namespace rps

int main()
{
    std::fstream file("input.txt");
    if (!file)
        return -1;

    int total_p1{0};

    for (std::string line; std::getline(file, line);)
        total_p1 += rps::score(line);

    std::cout << total_p1 << '\n';

    return 0;
}