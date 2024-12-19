/**
 * @file HandlerVector.h
 * @brief Заголовочный файл класса HandlerVector.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <limits>

/**
 * @class HandlerVector
 * @brief Класс для обработки целочисленных векторов.
 *
 *  Предоставляет статический метод processVector для вычисления суммы квадратов элементов вектора.
 *  Обрабатывает возможные переполнения.
 */
class HandlerVector {
public:
    /**
     * @brief Вычисляет сумму квадратов элементов вектора.
     * @param vectorValues Входной вектор целых чисел.
     * @return Сумма квадратов элементов вектора, преобразованная в int32_t.
     *         Возвращает максимальное или минимальное значение int32_t в случае переполнения.
     */
    static int32_t processVector(const std::vector<int32_t>& vectorValues);
};
