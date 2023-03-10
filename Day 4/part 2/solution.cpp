#include <fstream>
#include <iostream>

struct Range
{
    int start_;
    int end_;
};

std::istream& operator>>(std::istream& is, Range& r)
{
    is >> r.start_;
    is.ignore(1, '-');
    is >> r.end_;

    return is;
}

constexpr bool overlap_(const Range one, const Range two)
{
    return (one.start_ <= two.start_ or one.start_ <= two.end_) and
           two.start_ <= one.end_;
}

int main()
{
    std::fstream file("input.txt");

    Range r1;
    Range r2;

    int overlapping_pairs = 0;

    char comma_holder = ' ';

    while (file >> r1 >> comma_holder >> r2)
    {
        if (overlap_(r1, r2))
            ++overlapping_pairs;
    }

    std::cout << overlapping_pairs << '\n';

    return 0;
}