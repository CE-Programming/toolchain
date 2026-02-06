#ifndef COMMON_H
#define COMMON_H

// #include "fake_iostream.h"

// using namespace fake;

#include <iostream>

using std::cout;
using std::ostream;

#define C(expr) if (!(expr)) { return __LINE__; }

#endif /* COMMON_H */
