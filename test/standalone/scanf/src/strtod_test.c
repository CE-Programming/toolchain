#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define B(expr) if (!(expr)) { return false; }

/**
 * @brief tests if strto(f/d/ld) sets endptr correctly
 */
static bool strtod_verify(const char* str, ptrdiff_t offset) {
    char* endptr;
    (void)strtod(str, &endptr);
    ptrdiff_t diff = (ptrdiff_t)(endptr - str);
    if (diff != offset) {
        return false;
    }
    return true;
}

bool strtod_test(void) {

    B(strtod_verify(""  , 0));
    B(strtod_verify("." , 0));
    B(strtod_verify("0.", 2));
    B(strtod_verify(".0", 2));
    B(strtod_verify(" " ""  , 0));
    B(strtod_verify(" " "." , 0));
    B(strtod_verify(" " "0.", 3));
    B(strtod_verify(" " ".0", 3));
    B(strtod_verify(""   "e", 0));
    B(strtod_verify("."  "e", 0));
    B(strtod_verify("0." "e", 2));
    B(strtod_verify(".0" "e", 2));
    B(strtod_verify(""   "e+", 0));
    B(strtod_verify("."  "e+", 0));
    B(strtod_verify("0." "e+", 2));
    B(strtod_verify(".0" "e+", 2));
    B(strtod_verify(""   "e1", 0));
    B(strtod_verify("."  "e1", 0));
    B(strtod_verify("0." "e1", 4));
    B(strtod_verify(".0" "e1", 4));
    B(strtod_verify(""   "e+1", 0));
    B(strtod_verify("."  "e+1", 0));
    B(strtod_verify("0." "e+1", 5));
    B(strtod_verify(".0" "e+1", 5));
    B(strtod_verify(" " ""   "e", 0));
    B(strtod_verify(" " "."  "e", 0));
    B(strtod_verify(" " "0." "e", 3));
    B(strtod_verify(" " ".0" "e", 3));
    B(strtod_verify(" " ""   "e+", 0));
    B(strtod_verify(" " "."  "e+", 0));
    B(strtod_verify(" " "0." "e+", 3));
    B(strtod_verify(" " ".0" "e+", 3));
    B(strtod_verify(" " ""   "e1", 0));
    B(strtod_verify(" " "."  "e1", 0));
    B(strtod_verify(" " "0." "e1", 5));
    B(strtod_verify(" " ".0" "e1", 5));
    B(strtod_verify(" " ""   "e+1", 0));
    B(strtod_verify(" " "."  "e+1", 0));
    B(strtod_verify(" " "0." "e+1", 6));
    B(strtod_verify(" " ".0" "e+1", 6));
    B(strtod_verify("+"  , 0));
    B(strtod_verify("+." , 0));
    B(strtod_verify("+0.", 3));
    B(strtod_verify("+.0", 3));
    B(strtod_verify(" " "+"  , 0));
    B(strtod_verify(" " "+." , 0));
    B(strtod_verify(" " "+0.", 4));
    B(strtod_verify(" " "+.0", 4));
    B(strtod_verify("+"   "e", 0));
    B(strtod_verify("+."  "e", 0));
    B(strtod_verify("+0." "e", 3));
    B(strtod_verify("+.0" "e", 3));
    B(strtod_verify("+"   "e+", 0));
    B(strtod_verify("+."  "e+", 0));
    B(strtod_verify("+0." "e+", 3));
    B(strtod_verify("+.0" "e+", 3));
    B(strtod_verify("+"   "e1", 0));
    B(strtod_verify("+."  "e1", 0));
    B(strtod_verify("+0." "e1", 5));
    B(strtod_verify("+.0" "e1", 5));
    B(strtod_verify("+"   "e+1", 0));
    B(strtod_verify("+."  "e+1", 0));
    B(strtod_verify("+0." "e+1", 6));
    B(strtod_verify("+.0" "e+1", 6));
    B(strtod_verify(" " "+"   "e", 0));
    B(strtod_verify(" " "+."  "e", 0));
    B(strtod_verify(" " "+0." "e", 4));
    B(strtod_verify(" " "+.0" "e", 4));
    B(strtod_verify(" " "+"   "e+", 0));
    B(strtod_verify(" " "+."  "e+", 0));
    B(strtod_verify(" " "+0." "e+", 4));
    B(strtod_verify(" " "+.0" "e+", 4));
    B(strtod_verify(" " "+"   "e1", 0));
    B(strtod_verify(" " "+."  "e1", 0));
    B(strtod_verify(" " "+0." "e1", 6));
    B(strtod_verify(" " "+.0" "e1", 6));
    B(strtod_verify(" " "+"   "e+1", 0));
    B(strtod_verify(" " "+."  "e+1", 0));
    B(strtod_verify(" " "+0." "e+1", 7));
    B(strtod_verify(" " "+.0" "e+1", 7));

    B(strtod_verify(""   "r", 0));
    B(strtod_verify("."  "r", 0));
    B(strtod_verify("0." "r", 2));
    B(strtod_verify(".0" "r", 2));
    B(strtod_verify(" " ""   "r", 0));
    B(strtod_verify(" " "."  "r", 0));
    B(strtod_verify(" " "0." "r", 3));
    B(strtod_verify(" " ".0" "r", 3));
    B(strtod_verify(""   "e" "r", 0));
    B(strtod_verify("."  "e" "r", 0));
    B(strtod_verify("0." "e" "r", 2));
    B(strtod_verify(".0" "e" "r", 2));
    B(strtod_verify(""   "e+" "r", 0));
    B(strtod_verify("."  "e+" "r", 0));
    B(strtod_verify("0." "e+" "r", 2));
    B(strtod_verify(".0" "e+" "r", 2));
    B(strtod_verify(""   "e1" "r", 0));
    B(strtod_verify("."  "e1" "r", 0));
    B(strtod_verify("0." "e1" "r", 4));
    B(strtod_verify(".0" "e1" "r", 4));
    B(strtod_verify(""   "e+1" "r", 0));
    B(strtod_verify("."  "e+1" "r", 0));
    B(strtod_verify("0." "e+1" "r", 5));
    B(strtod_verify(".0" "e+1" "r", 5));
    B(strtod_verify(" " ""   "e" "r", 0));
    B(strtod_verify(" " "."  "e" "r", 0));
    B(strtod_verify(" " "0." "e" "r", 3));
    B(strtod_verify(" " ".0" "e" "r", 3));
    B(strtod_verify(" " ""   "e+" "r", 0));
    B(strtod_verify(" " "."  "e+" "r", 0));
    B(strtod_verify(" " "0." "e+" "r", 3));
    B(strtod_verify(" " ".0" "e+" "r", 3));
    B(strtod_verify(" " ""   "e1" "r", 0));
    B(strtod_verify(" " "."  "e1" "r", 0));
    B(strtod_verify(" " "0." "e1" "r", 5));
    B(strtod_verify(" " ".0" "e1" "r", 5));
    B(strtod_verify(" " ""   "e+1" "r", 0));
    B(strtod_verify(" " "."  "e+1" "r", 0));
    B(strtod_verify(" " "0." "e+1" "r", 6));
    B(strtod_verify(" " ".0" "e+1" "r", 6));
    B(strtod_verify("+"   "r", 0));
    B(strtod_verify("+."  "r", 0));
    B(strtod_verify("+0." "r", 3));
    B(strtod_verify("+.0" "r", 3));
    B(strtod_verify(" " "+"   "r", 0));
    B(strtod_verify(" " "+."  "r", 0));
    B(strtod_verify(" " "+0." "r", 4));
    B(strtod_verify(" " "+.0" "r", 4));
    B(strtod_verify("+"   "e" "r", 0));
    B(strtod_verify("+."  "e" "r", 0));
    B(strtod_verify("+0." "e" "r", 3));
    B(strtod_verify("+.0" "e" "r", 3));
    B(strtod_verify("+"   "e+" "r", 0));
    B(strtod_verify("+."  "e+" "r", 0));
    B(strtod_verify("+0." "e+" "r", 3));
    B(strtod_verify("+.0" "e+" "r", 3));
    B(strtod_verify("+"   "e1" "r", 0));
    B(strtod_verify("+."  "e1" "r", 0));
    B(strtod_verify("+0." "e1" "r", 5));
    B(strtod_verify("+.0" "e1" "r", 5));
    B(strtod_verify("+"   "e+1" "r", 0));
    B(strtod_verify("+."  "e+1" "r", 0));
    B(strtod_verify("+0." "e+1" "r", 6));
    B(strtod_verify("+.0" "e+1" "r", 6));
    B(strtod_verify(" " "+"   "e" "r", 0));
    B(strtod_verify(" " "+."  "e" "r", 0));
    B(strtod_verify(" " "+0." "e" "r", 4));
    B(strtod_verify(" " "+.0" "e" "r", 4));
    B(strtod_verify(" " "+"   "e+" "r", 0));
    B(strtod_verify(" " "+."  "e+" "r", 0));
    B(strtod_verify(" " "+0." "e+" "r", 4));
    B(strtod_verify(" " "+.0" "e+" "r", 4));
    B(strtod_verify(" " "+"   "e1" "r", 0));
    B(strtod_verify(" " "+."  "e1" "r", 0));
    B(strtod_verify(" " "+0." "e1" "r", 6));
    B(strtod_verify(" " "+.0" "e1" "r", 6));
    B(strtod_verify(" " "+"   "e+1" "r", 0));
    B(strtod_verify(" " "+."  "e+1" "r", 0));
    B(strtod_verify(" " "+0." "e+1" "r", 7));
    B(strtod_verify(" " "+.0" "e+1" "r", 7));

    return true;
}
