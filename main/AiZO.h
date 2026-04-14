#pragma once
#include "../sorting/abstractSort.h"
#include "../sorting/binary sort/binarySort.h"
#include "../sorting/heap sort/heapSort.h"
#include "../sorting/quick sort/quickSort.h"
#include "../sorting/insertion sort/insertionSort.h"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>

using namespace std;

template <typename T>
class Manager {
private:
    Sorter<T>* sorter;
    T* array;
    int size;

    chrono::milliseconds sortingTime;

    // Generuje całkowicie losową tablicę (0% posortowana)
    void generate_array_random() {
        cout << "Podaj dlugosc tablicy: ";
        cin >> size;

        array = new T[size];

        for (int i = 0; i < size; ++i) {
            array[i] = static_cast<T>(rand() % 100000);
        }
        cout << "Wygenerowano tablice losowa (0% posortowana).\n";
    }

    // Generuje tablicę posortowaną w 1/3 (33%)
    void generate_array_sorted_33() {
        cout << "Podaj dlugosc tablicy: ";
        cin >> size;

        array = new T[size];

        // Generujemy losowe wartości
        for (int i = 0; i < size; ++i) {
            array[i] = static_cast<T>(rand() % 100000);
        }

        // Sortujemy pierwszą 1/3 tablicy
        int sortedPart = size / 3;
        if (sortedPart > 0) {
            sort(array, array + sortedPart);
        }

        cout << "Wygenerowano tablice posortowana w 33% (pierwsza 1/3).\n";
    }

    // Generuje tablicę posortowaną w 1/2 (50%)
    void generate_array_sorted_50() {
        cout << "Podaj dlugosc tablicy: ";
        cin >> size;

        array = new T[size];

        // Generujemy losowe wartości
        for (int i = 0; i < size; ++i) {
            array[i] = static_cast<T>(rand() % 100000);
        }

        // Sortujemy pierwszą połowę tablicy
        int sortedPart = size / 2;
        if (sortedPart > 0) {
            sort(array, array + sortedPart);
        }

        cout << "Wygenerowano tablice posortowana w 50% (pierwsza polowa).\n";
    }

    // Menu wyboru stopnia posortowania
    void choose_array_type() {
        int wybor;

        cout << "\n========================================\n";
        cout << "Wybierz stopien posortowania tablicy:\n";
        cout << "========================================\n";
        cout << "1. 0%  - tablica calkowicie losowa\n";
        cout << "2. 33% - tablica posortowana w 1/3\n";
        cout << "3. 50% - tablica posortowana w 1/2\n";
        cout << "========================================\n";
        cout << "Wybierz (1-3): ";
        cin >> wybor;

        // Zwolnij poprzednią tablicę jeśli istnieje
        if (array != nullptr) {
            delete[] array;
            array = nullptr;
        }

        switch (wybor) {
        case 1:
            generate_array_random();
            break;
        case 2:
            generate_array_sorted_33();
            break;
        case 3:
            generate_array_sorted_50();
            break;
        default:
            cout << "Nieprawidlowy wybor. Generuje tablice losowa.\n";
            generate_array_random();
            break;
        }

        print_array();
    }

    template <typename Func>
    void measure_time(Func f) {
        auto start = chrono::high_resolution_clock::now();
        f();
        auto end = chrono::high_resolution_clock::now();

        sortingTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    }

    void run_sort(int wybor) {

        if (sorter != nullptr) {
            delete sorter;
            sorter = nullptr;
        }

        switch (wybor) {
        case 1:
            sorter = new HeapSort<T>(array, size);
            break;
        case 2:
            sorter = new QuickSort<T>(array, size);
            break;
        case 3:
            sorter = new InsertionSort<T>(array, size);
            break;
        case 4:
            sorter = new BinarySort<T>(array, size);
            break;
        default:
            return;
        }

        measure_time([&]() { return sorter->Sort(); });
    }

public:
    // Konstruktor bez automatycznego generowania tablicy
    Manager() : sorter(nullptr), array(nullptr), size(0) {
        // Tablica będzie generowana przez menu
    }

    ~Manager() {
        delete[] array;
        if (sorter != nullptr) {
            delete sorter;
        }
    }

    void print_array() {
        if (size == 0 || array == nullptr) {
            cout << "Tablica jest pusta!\n";
            return;
        }

        bool isCorrect = true;
        if (this->size > 0) {
            cout << array[0] << " ";
        }
        if (this->size > 1) {
            T prev = array[0];
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

    void menu() {
        choose_array_type();

        int wybor;

        cout << "\n========================================\n";
        cout << "Wybierz algorytm sortowania (1-4):\n";
        cout << "========================================\n";
        cout << "1. Heap Sort\n";
        cout << "2. Quick Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Binary Sort\n";
        cout << "========================================\n";
        cout << "Wybierz: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            cout << "Uruchamianie Heap Sort...\n";
            run_sort(wybor);
            break;
        case 2:
            cout << "Uruchamianie Quick Sort...\n";
            run_sort(wybor);
            break;
        case 3:
            cout << "Uruchamianie Insertion Sort...\n";
            run_sort(wybor);
            break;
        case 4:
            cout << "Uruchamianie Binary Sort...\n";
            run_sort(wybor);
            break;
        default:
            cout << "Nieprawidlowy wybor. Koniec programu.\n";
            return;
        }

        cout << "\n========== WYNIK ==========\n";
        sorter->print_array();

        cout << "Czas wykonania: " << sortingTime.count() << " ms\n";
    }
};