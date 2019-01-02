#include "utils.hpp"

#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

namespace utils
{

int generate_random(const int min, const int max)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

std::queue<std::string> shuffle_domain(std::vector<std::string>& vec_domain)
{

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(vec_domain), std::end(vec_domain), e);

    std::queue<std::string> shuffled_domain;
    for(const std::string& word : vec_domain)
        shuffled_domain.push(word);

    return shuffled_domain;
}

void visualise_board(std::vector<char> board)
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            std::cout << board[y * 10 + x] << " ";
        }
        std::cout << std::endl;
    }
}

}
