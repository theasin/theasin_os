#pragma once
#include "types.h"
#ifndef MATH_H
#define MATH_H
extern "C" {
    u64 pow(int base, int exp)
    {
        if(exp < 0)
        return -1;

        int result = 1;
        while (exp)
        {
            if (exp & 1)
                result *= base;
            exp >>= 1;
            base *= base;
        }

        return result;
    }
}
#endif /* MATH_H */