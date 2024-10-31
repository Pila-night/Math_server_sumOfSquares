#include "HandlerVector.h"

#include <vector>
#include <limits>
#include <cstdint>

int32_t HandlerVector::processVector(const std::vector<int32_t>& vectorValues) {
    int64_t sumOfSquares = 0;
    const int64_t maxVal = std::numeric_limits<int32_t>::max(); 
    const int64_t minVal = std::numeric_limits<int32_t>::min();

    for (int32_t value : vectorValues) {
        int64_t square = static_cast<int64_t>(value) * value;

        if (sumOfSquares < minVal + square) {
            return static_cast<int32_t>(minVal);     // тут -2^32 при переполнении вниз
        }

        if (sumOfSquares > maxVal - square) {
            return static_cast<int32_t>(maxVal - 1); // 2^31 - 1 при переполнении вверх
        }

        sumOfSquares += square;
    }

    return static_cast<int32_t>(sumOfSquares);
}