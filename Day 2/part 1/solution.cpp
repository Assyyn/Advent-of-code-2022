#include "RPS.h"

#include <fstream>
#include <iostream>
#include <utility>

int main()
{
    std::fstream file{"input.txt"};
    if (!file)
    {
        std::cerr << "Could not open file!\n";
        return -1;
    }

    char p1, p2;
    int p1_score{0}, p2_score{0};

    while (file >> p1 >> p2)
    {
        std::pair<int, int> scores{rps::calculate_scores(p1, p2)};
        p1_score += scores.first;
        p2_score += scores.second;
    }

    std::cout << "P1 score: " << p1_score << ", P2 score: " << p2_score << '\n';

    return 0;
}