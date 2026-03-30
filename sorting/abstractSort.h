#pragma once
#include <algorithm>
#include <iostream>

// Abstrakcyjna klasa bazowa dla algorytmów sortowania - -techniki programowania obiektowego

template <typename T>
class Sorter {
protected: // Zmienne widoczne dla klas dziedzicz¹cych
    T* array;
    int size;

public:
    Sorter(T* arr, int s) {
        size = s;
        array = new T[size];
        for (int i = 0; i < size; ++i) { // kopia tablicy
            array[i] = arr[i];
        }
    }

    virtual ~Sorter() {
        delete[] array;
    }

    virtual void Sort() = 0;

    // Wyœwietlanie tablicy korzystaj¹ce z pól klasy
    void print_array() {
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};
