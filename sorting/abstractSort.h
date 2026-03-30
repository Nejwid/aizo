#pragma once
#include <algorithm>
#include <iostream>
using namespace::std;

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

	void print_array() {
		bool isCorrect = true;
		if (this->size > 0) {
			cout << array[0] << " ";
		}
		if (this->size > 1) {
			T prev = array[0]; // Zmiana int na T dla spójnoœci typu
			for (int i = 1; i < size; ++i) {
				if (array[i] < prev) {
					isCorrect = false;
				}
				cout << array[i] << " ";
				prev = array[i];
			}
		}
		cout << "\nczy tablica jest posortowana? 1 tak, 0 nie: " << isCorrect << endl;
	}
};
