#include <charconv>
#include <string_view>
#include <system_error>

#include "common.h"

void show_to_chars(auto... format_args) {
    const size_t buf_size = 10;
    char buf[buf_size]{};
    std::to_chars_result result = std::to_chars(buf, buf + buf_size, format_args...);

    if (result.ec != std::errc()) {
        cout << std::make_error_code(result.ec).message() << '\n';
    } else {
        std::string_view str(buf, result.ptr - buf);
        cout << str << '\n';
    }
}

int test_charconv() {
    show_to_chars(42);
    // These will blow up the binary size
    #if 0
        show_to_chars(+3.14159F);
        show_to_chars(-3.14159, std::chars_format::fixed);
        show_to_chars(-3.14159, std::chars_format::scientific, 3);
        show_to_chars(3.1415926535, std::chars_format::fixed, 10);
    #endif
    return 0;
}
