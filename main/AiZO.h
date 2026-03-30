#pragma once
#include "../sorting/abstractSort.h"
#include "../sorting/binary sort/binarySort.h"
#include "../sorting/heap sort/heapSort.h"
#include "../sorting/quick sort/quickSort.h"
#include "../sorting/insertion sort/insertionSort.h"

#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

template <typename T>
class Manager {
private:
	Sorter<T>* sorter; // wskaznik na algorytm
	T* array;          // tablica
	int size;          // rozmiar tablicy

	chrono::milliseconds sortingTime;

	void generate_array() {
		cout << "Podaj dlugosc tablicy: ";
		cin >> size;

		array = new T[size];

		for (int i = 0; i < size; ++i) {
			array[i] = static_cast<T>(rand() % 100000); // losowanie liczb
		}
	}

	// Szablon dla funkcji pomiaru czasu (naprawia błąd składni i wskaźników na funkcję)
	template <typename Func>
	void measure_time(Func f) {
		auto start = chrono::high_resolution_clock::now();
		f();
		auto end = chrono::high_resolution_clock::now();

		// zmiana jednostki na milisekundy za pomoca std::milli
		sortingTime = chrono::duration_cast<chrono::milliseconds>(end - start);;
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

		// Przekazanie do measure_time jako wyrażenie lambda
		measure_time([&]() { return sorter->Sort(); });
	}

public:
	Manager() : sorter(nullptr), array(nullptr), size(0) {
		generate_array();
		print_array();
	}

	~Manager() {
		delete[] array;
		if (sorter != nullptr) {
			delete sorter;
		}
	}

	void print_array() {
		bool isCorrect = true;
		if (this->size > 0) {
			cout << array[0] << " ";
		}
		if (this->size > 1) {
			T prev = array[0]; // Zmiana int na T dla spójności typu
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
		int wybor;

		cout << "Wybierz algorytm sortowania (1-4):\n";
		cout << "1. Heap Sort\n";
		cout << "2. Quick Sort\n";
		cout << "3. Insertion Sort\n";
		cout << "4. Binary Sort\n";
		cout << "Wybierz... : ";
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
			cout << "Nieprawidłowy wybór. Koniec programu.\n";
			break;
		}

		sorter->print_array();

		cout << "Czas wykonania: " << sortingTime.count() << " ms\n";
	}
};