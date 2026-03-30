#pragma once
#include <algorithm>
#include "../abstractSort.h"

template <typename T>
class HeapSort : public Sorter<T> {
private:
    // Funkcja pomocnicza do naprawy kopca korzystaj¹ca z this->array
    void Fix(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && this->array[left] > this->array[largest])
            largest = left;

        if (right < n && this->array[right] > this->array[largest])
            largest = right;

        if (largest != i) {
            std::swap(this->array[i], this->array[largest]);
            Fix(n, largest);
        }
    }

public:
    // Wywo³anie konstruktora klasy bazowej
    HeapSort(T* arr, int s) : Sorter<T>(arr, s) {}

    // Nadpisanie metody bez argumentów
    void Sort() override {
        int n = this->size;

        // Budowanie kopca
        for (int i = n / 2 - 1; i >= 0; i--)
            Fix(n, i);

        // Wyci¹ganie elementów z kopca
        for (int i = n - 1; i > 0; i--) {
            std::swap(this->array[0], this->array[i]);
            Fix(i, 0);
        }
    }
};