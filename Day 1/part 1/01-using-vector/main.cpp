#include "Timer.h"
// average time: 0.00089s

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

    std::vector<int> calories;

    Timer t;
    while (!fileIN.eof())
    {
        std::getline(fileIN, line);
        if (line == "")
        {
            calories.push_back(sum);
            sum = 0;
        }
        else
        {
            int x{};
            std::stringstream ss{line};
            ss >> x;
            sum += x;
        }
    }
    calories.push_back(sum);
    std::sort(calories.begin(), calories.end());

    double timeTaken{t.elapsed()};
    std::cout << calories.back() << ", " << timeTaken << "s\n";

    return 0;
}