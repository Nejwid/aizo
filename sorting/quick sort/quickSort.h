#pragma once
#include "../abstractSort.h"
#include <algorithm>

template <typename T>
class QuickSort : public Sorter<T> {
private:
    // poprawna metoda QuickSort operujaca na this->array
    void SortRec(int left, int right) {
        int i = left;
        int j = right;
        T pivot = this->array[(left + right) / 2];

        while (i <= j) {
            while (this->array[i] < pivot) i++;
            while (this->array[j] > pivot) j--;

            if (i <= j) {
                std::swap(this->array[i], this->array[j]);
                i++;
                j--;
            }
        }

        if (left < j)
            SortRec(left, j);

        if (i < right)
            SortRec(i, right);
    }

public:
    // wywolanie konstruktora klasy bazowej (kopiowanie tablicy)
    QuickSort(T* arr, int s) : Sorter<T>(arr, s) {}

    // nadpisanie metody bez argumentow
    void Sort() override {
        if (this->size > 0) {
            SortRec(0, this->size - 1);
        }
    }
};