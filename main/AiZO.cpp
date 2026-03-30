#include "AiZO.h"

using namespace std;

int main()
{
    int select;

    cout << "Wybierz typ danych tablicy:\n";
    cout << "1. int\n";
    cout << "2. float\n";
    cout << "Wybierz madrze... : ";
    cin >> select;

    // Tworzenie odpowiedniej instancji klasy Manager
    if (select == 1) {
        Manager<int> manager;
        manager.menu();
    }
    else if (select == 2) {
        Manager<float> manager;
        manager.menu();
    }
    else {
        cout << "Nieprawidłowy wybór. Koniec programu.\n";
        return 96;
    }
    return 0;
}
