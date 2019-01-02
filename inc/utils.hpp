#pragma once

#include <queue>
#include <vector>
#include <string>

namespace utils
{
    int generate_random(const int, const int);
    std::queue<std::string> shuffle_domain(std::vector<std::string>&);
    void visualise_board(std::vector<char>);
}
