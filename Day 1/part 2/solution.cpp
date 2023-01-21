#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream fileIN{"aoc1.txt"};

    std::string line;
    int sum{0};

    std::vector<int> calories(239);

    while (!fileIN.eof())
    {
        std::getline(fileIN, line);
        if (line == "") // if we encounter an empty line, push to the vector the
                        // sum of the grouped numbers
        {
            calories.push_back(sum);
            sum = 0;
        }
        else
        {
            int x;
            std::stringstream ss{line};
            ss >> x;
            sum += x;
        }
    }

    //  after hitting EOF, we forgot to push_back() the sum
    calories.push_back(sum);

    std::sort(calories.begin(), calories.end());

    std::size_t size{calories.size()};
    int top3{calories.back() + calories.at(size - 2) + calories.at(size - 3)};
    std::cout << top3 << '\n';

    return 0;
}