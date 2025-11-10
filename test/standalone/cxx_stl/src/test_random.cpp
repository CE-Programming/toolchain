#include <map>
#include <random>
#include <string>
#include <chrono>

#include "common.h"

int test_random()
{
    uint64_t seed = static_cast<uint64_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    std::mt19937 gen(seed);

    // If an event occurs 3 times a minute on average, how
    // often is it that it occurs n times in one minute?
    std::poisson_distribution<> d(3);

    std::map<int, int> hist;
    for (int n = 0; n != 64; ++n) {
        ++hist[d(gen)];
    }

    for (auto [x, y] : hist) {
        printf("%2d %s\n", x, std::string(y, '*').c_str());
    }
    return 0;
}
