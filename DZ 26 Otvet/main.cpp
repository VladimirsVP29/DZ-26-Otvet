#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <chrono>
#include "array.h"

int main() {
    //int N = 20;                       //размер массива
    int N = 10'000'000;                 //размер массива
    int M = 10;                         //количество частей, на которые разбивается массив

    Array array(N, M);                  //создать массив

    //array.showArray();
    //std::cout << "\n\n";

    std::cout << "N (array size): " << array.getN() << " elements" << std::endl;
    std::cout << "M (number of parts the array is split into): " << array.getM() << "\n" << std::endl;

    //начало отсчета времени в основном потоке
    auto timeStart = std::chrono::system_clock::now();
    //сумма элементов массива, подсчитанная в основном потоке
    int sum1 = array.calculateAllSum();

    //конец отсчета времени в основном потоке
    auto timeEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = timeEnd - timeStart;
    //вывод суммы и затраченного времени в основном потоке
    std::cout << "In the main thread:\t sum = " << sum1 << "\t time = " << diff.count() << std::endl;

    //начало отсчета времени в М потоках
    timeStart = std::chrono::system_clock::now();

    //определить количество элементов в частях
    size_t countElementsInPart = array.getN() / array.getM();
    //объявление вектора потоков
    std::vector<std::thread> threads;

    //сумма элементов массива, подсчитанная в М потоках
    int sum2 = 0;

    //добавить в поток значения для расчетов, кроме последней части массива
    for (size_t i = 0; i < array.getM() - 1; ++i) {
        threads.push_back(std::thread([i, countElementsInPart, &array, &sum2]() {
            //левый индекс в i части массива
            size_t leftIndex = countElementsInPart * i;
            //правый индекс в i части массива
            size_t rightIndex = leftIndex + countElementsInPart;
            sum2 += array.calculateSum(leftIndex, rightIndex);
            }));
    }

    //добавить последнюю часть массива в поток
    threads.push_back(std::thread([countElementsInPart, &array, &sum2]() {
        //левый индекс в послед.части массива
        size_t leftIndex = countElementsInPart * (array.getM() - 1);
        //правый индекс в послед.части массива
        size_t rightIndex = array.getN();
        sum2 += array.calculateSum(leftIndex, rightIndex);
        }));

    //ожидание завершения работы потоков
    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });

    //конец отсчета времени
    timeEnd = std::chrono::system_clock::now();
    diff = timeEnd - timeStart;
    //вывод суммы и затраченного времени в потоках
    std::cout << "In " << array.getM() << " threads:\t\t sum = " << sum2 << "\t time = " << diff.count() << std::endl;

    return 0;
}