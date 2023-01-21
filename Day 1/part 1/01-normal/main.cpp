#include "Timer.h"
// average time: 0.00093s

#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::ifstream fileIN{"aoc1.txt"};

    std::string line;
    int greatest{0};
    int sum{0};

    Timer t;
    while (!fileIN.eof())
    {
        std::getline(fileIN, line);
        if (line == "")
        {
            greatest < sum ? greatest = sum : 0;
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
    auto timeTaken{t.elapsed()};

    std::cout << greatest << ", " << timeTaken << "s\n";

    return 0;
}