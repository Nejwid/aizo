#pragma once
#include <algorithm>
#include "../abstractSort.h"

// JEST TO NADAL INSERTION SORT A NIE DRZEWO BST ani w ogole zadne drzewo

// klasa z szablonem - dla roznych typow danych jedna klasa
template <typename T>
class BinarySort : public Sorter<T> {
public:
    // Wywo³anie konstruktora klasy bazowej do skopiowania tablicy
    BinarySort(T* arr, int s) : Sorter<T>(arr, s) {}

    // Nadpisanie metody bez argumentów
    void Sort() override {
        int i, j, ip, ik;
        T x;
        int n = this->size;

        // Przechodzenie tablicy od przedostatniego elementu
        for (j = n - 2; j >= 0; j--) {
            x = this->array[j];
            ip = j;
            ik = n;

            // Binarne szukanie miejsca wstawienia
            while (ik - ip > 1) {
                i = (ip + ik) / 2;
                if (x <= this->array[i]) ik = i;
                else ip = i;
            }

            // Przesuwanie elementów w lewo
            for (i = j; i < ip; i++) {
                this->array[i] = this->array[i + 1];
            }

            // Wstawienie elementu na w³aœciwe miejsce
            this->array[ip] = x;
        }
    }
};