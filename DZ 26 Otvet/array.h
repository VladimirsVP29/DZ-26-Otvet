#pragma once

class Array {
	std::shared_ptr<int[]> array_;	//массив
	size_t n_;						//количество элементов массива
	size_t m_;						//количество частей, на которые разбивается массив

public:
	Array() : array_(nullptr), n_(0), m_(0) {}
	Array(size_t n, size_t m);
	~Array() = default;

	//Подсчитать сумму в части массива
	int calculateSum(size_t start, size_t end) const;

	//Подсчитать всю сумму массива
	int calculateAllSum() const;

	//Показать массив
	void showArray() const;

	//Получить массив
	std::shared_ptr<int[]> getArray() const;

	//Получить n
	size_t getN() const;

	//Получить m
	size_t getM() const;
};