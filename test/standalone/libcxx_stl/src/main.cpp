#include <algorithm>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include <stdio.h>
#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/sprintf.h>

#define C(expr) if (!(expr)) { return __LINE__; }

static int run_tests() {
    std::vector<int> values{9, 2, 7, 1};
    values.push_back(3);
    std::sort(values.begin(), values.end());
    C(values.front() == 1 && values.back() == 9);
    C(std::binary_search(values.begin(), values.end(), 7));

    std::string text("a string long enough to require heap allocation");
    text += " on the CE";
    C(text.substr(text.size() - 9) == "on the CE");
    C(text.find("heap") != std::string::npos);

    auto owned = std::make_unique<std::string>(text);
    C(*owned == text);
    std::optional<std::string> maybe(*owned);
    C(maybe.has_value() && *maybe == text);
    maybe.reset();
    C(!maybe.has_value());

    // LLVM 22.1.8 fixes extraction to select the first equivalent element.
    std::multimap<int, int> map{{1, 10}, {1, 20}, {1, 30}};
    auto node = map.extract(1);
    C(!node.empty() && node.mapped() == 10);
    C(map.size() == 2 && map.begin()->second == 20);

    std::multiset<int> set{1, 1, 2};
    auto first = set.begin();
    auto second = std::next(first);
    auto* second_address = &*second;
    auto set_node = set.extract(1);
    C(!set_node.empty() && set_node.value() == 1);
    C(set.size() == 2 && &*set.begin() == second_address);
    return 0;
}

extern "C" int main() {
    os_ClrHome();
    int failed_test = run_tests();
    if (failed_test != 0) {
        char buf[sizeof("Failed test L-8388608")];
        boot_sprintf(buf, "Failed test L%d", failed_test);
        puts(buf);
    } else {
        puts("All tests passed");
    }
    while (!os_GetCSC());
    return 0;
}
