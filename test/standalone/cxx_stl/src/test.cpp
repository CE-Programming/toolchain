#include <vector>
#include <algorithm>
#include <numeric>

#define C(expr) if (!(expr)) { return __LINE__; }

int test() {
    std::vector<int> x = {8, 4, 5, 9};
    x.push_back(std::move(6));
    x.push_back(9);
    x[2] = -1;
    std::sort(x.begin(), x.end());
    std::vector<int> y = {7, 3};
    std::swap(x, y);
    std::swap(y.front(), y.back());
    x.insert(x.end(), y.rbegin(), y.rend());

    const std::vector<int> x_truth = {7, 3, -1, 9, 8, 6, 4, 9};
    constexpr int x_sum = 45;

    C((x.size() == x_truth.size()));
    C((y.size() == x_truth.size() - 2));
    C((std::accumulate(x.begin(), x.end(), decltype(x)::value_type(0)) == x_sum));
    C((std::equal(x.begin(), x.end(), x_truth.begin())));
    C((std::equal(y.rbegin(), y.rend(), x_truth.begin() + 2)));

    return 0;
}
