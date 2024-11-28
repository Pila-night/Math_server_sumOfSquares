/**
 * @file HandlerVector.cpp
 * @brief Реализация класса HandlerVector.
 */
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
        // Проверка на переполнение до сложения
        if (sumOfSquares > maxVal - square) {
            return static_cast<int32_t>(maxVal); 
        }
        sumOfSquares += square;
        // Проверка на переполнение после сложения
        if (sumOfSquares > maxVal) {
            return static_cast<int32_t>(maxVal);
        }
        if (sumOfSquares < minVal) {
            return static_cast<int32_t>(minVal);
        }
    }
    return static_cast<int32_t>(sumOfSquares);
}
