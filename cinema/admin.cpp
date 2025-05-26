#include "admin.h"
#include "movie.h"
#include "studio.h"
#include <iostream>
using namespace std;

bool AdminUI() {
    int pilih;
    cout << "1. Show Movie\n";
    cout << "2. Create Movie\n";
    cout << "3. Update Movie\n";
    cout << "4. Update Session\n";
    cout << "5. Update Time\n";
    cout << "6. Logout\n";
    cout << "Pilih : "; cin >> pilih;
    system("cls");
    switch (pilih) {
        case 1: ShowsMovie(); break;
        case 2: CreateMovie(); break;
        case 3: UpdateMovie(); break;
        case 4: UpdateSession(); break;
        case 5: UpdateTime(); break;
        case 6: return false;
        default: break;
    }
    system("pause");
    return true;
}