#include <iostream>
#include "array.h"

Array::Array(size_t n, size_t m) : n_(n), m_(m) {
    //создать массив
    array_ = std::shared_ptr<int[]>(new int[n_], std::default_delete<int[]>());
    //заполнить массив случайными числами
    srand(time(NULL));
    for (size_t i = 0; i < n_; ++i) {
        array_[i] = rand() % 99 + 1;
    }
}

//Подсчитать сумму в части массива
int Array::calculateSum(size_t left, size_t right) const {
    int sum = 0;
    while (left < right) {
        sum += array_[left++];
    }
    return sum;
}

//Подсчитать всю сумму массива
int Array::calculateAllSum() const {
    int sum = 0;
    size_t i = 0;
    while (i < n_) {
        sum += array_[i++];
    }
    return sum;
}

//Показать массив
void Array::showArray() const {
    std::cout << "array: ";
    for (size_t i = 0; i < n_; ++i) {
        std::cout << array_[i] << " ";
    }
    std::cout << std::endl;
}

//Получить массив
std::shared_ptr<int[]> Array::getArray() const {
    return array_;
}

//Получить n
size_t Array::getN() const {
    return n_;
}

//Получить m
size_t Array::getM() const {
    return m_;
}