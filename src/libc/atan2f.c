/* Copyright (c) 2000-2008 Zilog, Inc. */
#include <math.h>
#include "__float32_constants.h"

float _atan2f_c(float arg1, float arg2) {
    float satan(float);

    if ((arg1+arg2)==arg1) {
        if (arg1 >= 0.0f) {
            return (F32_PI2);
        } else {
            return (-F32_PI2);
        }
    } else if (arg2 < 0.0f) {
        if(arg1 >= 0.0f) {
            return (F32_PI - satan(-arg1/arg2));
        } else {
            return (-F32_PI + satan(arg1/arg2));
        }
    } else if (arg1 > 0.0f) {
        return (satan(arg1/arg2));
    } else {
        return (-satan(-arg1/arg2));
    }
}

double _atan2_c(double, double) __attribute__((alias("_atan2f_c")));
