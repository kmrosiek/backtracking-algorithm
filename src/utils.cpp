#include "utils.hpp"

#include <random>

namespace utils
{

int generate_random(const int min, const int max)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

}
