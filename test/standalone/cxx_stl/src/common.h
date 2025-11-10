#ifndef COMMON_H
#define COMMON_H

#include "fake_iostream.h"

using namespace fake;

#define C(expr) if (!(expr)) { return __LINE__; }

#endif /* COMMON_H */
