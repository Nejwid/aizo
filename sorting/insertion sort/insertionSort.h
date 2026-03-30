#pragma once
#include <algorithm>
#include "../abstractSort.h"

template <typename T>
class InsertionSort : public Sorter<T> {
public:
    // Wywo³anie konstruktora klasy bazowej do skopiowania tablicy
    InsertionSort(T* arr, int s) : Sorter<T>(arr, s) {}

    // Nadpisanie metody bez argumentów
    void Sort() override {
        for (int i = 1; i < this->size; i++) {
            T key = this->array[i];
            int j = i - 1;

            // Przesuwanie elementów wiêkszych od klucza
            while (j >= 0 && this->array[j] > key) {
                this->array[j + 1] = this->array[j];
                --j;
            }
            this->array[j + 1] = key;
        }
    }
};