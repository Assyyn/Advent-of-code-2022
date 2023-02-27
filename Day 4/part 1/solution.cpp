#include <fstream>
#include <iostream>
#include <sstream>

/// @brief a closed interval of numbers : [start, end]
struct Range
{
    int start{};
    int end{};
};

std::istream& operator>>(std::istream& is, Range& range)
{
    is >> range.start;
    is.ignore(1, '-');
    is >> range.end;

    return is;
}

/// @brief Test if one of the given ranges fully contains the other
/// @param one first range
/// @param two second range
/// @return true if any of the two fully contains the other, false otherwise
bool contains_another(const Range& one, const Range& two)
{
    return (one.start <= two.start && one.end >= two.end) ||
           (two.start <= one.start && two.end >= one.end);
}

int main()
{
    std::ifstream file("input.txt");
    std::stringstream stream;
    stream << file.rdbuf();

    Range first;
    Range second;

    char comma_holder{' '};

    int fully_contained_pairs = 0;

    while (stream >> first >> comma_holder >> second)
    {
        if (contains_another(first, second))
            ++fully_contained_pairs;
    }

    std::cout << fully_contained_pairs << '\n';
}
