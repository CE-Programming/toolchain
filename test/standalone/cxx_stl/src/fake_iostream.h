#ifndef FAKE_IOSTREAM_H
#define FAKE_IOSTREAM_H

#include <cstdio>
#include <string>
#include <string_view>

namespace fake {

struct ostream {};

static ostream cout;

inline ostream& operator<<(ostream& os, char c) {
    fputc(c, stdout);
    return os;
}

inline ostream& operator<<(ostream& os, const char* x) {
    printf("%s", x);
    return os;
}

inline ostream& operator<<(ostream& os, const std::string& x) {
    printf("%s", x.c_str());
    return os;
}

inline ostream& operator<<(ostream& os, const std::string_view& x) {
    fwrite(x.data(), sizeof(char), x.size(), stdout);
    return os;
}

inline ostream& operator<<(ostream& os, bool b) {
    #if 0
        fputc(b ? '1' : '0', stdout);
    #else
        os << (b ? "true" : "false");
    #endif
    return os;
}

inline ostream& operator<<(ostream& os, void const * x) {
    printf("%p", x);
    return os;
}

inline ostream& operator<<(ostream& os, void const volatile * x) {
    printf("%p", (void const*)x);
    return os;
}

inline ostream& operator<<(ostream& os, nullptr_t) {
    printf("%p", nullptr);
    return os;
}

inline ostream& operator<<(ostream& os, int x) {
    printf("%d", x);
    return os;
}

inline ostream& operator<<(ostream& os, unsigned int x) {
    printf("%u", x);
    return os;
}

inline ostream& operator<<(ostream& os, float x) {
    printf("%f", x);
    return os;
}

inline ostream& operator<<(ostream& os, double x) {
    printf("%f", x);
    return os;
}

constexpr char endl = '\n';
constexpr char ends = '\0';

constexpr char dec = '\0';
constexpr char oct = '\0';
constexpr char hex = '\0';
constexpr char basefield = '\0';
constexpr char left = '\0';
constexpr char right = '\0';
constexpr char internal = '\0';
constexpr char adjustfield = '\0';
constexpr char scientific = '\0';
constexpr char fixed = '\0';
constexpr char floatfield = '\0';
constexpr char boolalpha = '\0';
constexpr char showbase = '\0';
constexpr char showpoint = '\0';
constexpr char showpos = '\0';
constexpr char skipws = '\0';
constexpr char unitbuf = '\0';
constexpr char uppercase = '\0';

} // namespace fake

#endif /* FAKE_IOSTREAM_H */
