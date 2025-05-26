#include "auth.h"
#include "admin.h"
#include "cashier.h"
#include "movie.h"
#include "studio.h"

int main() {
    bool isAdmin;
    loadCashiersFromFile("cashiers.txt");
    while (login(isAdmin)) {
        if (isAdmin) {
            do {
                system("cls");
            } while (AdminUI());
        } else {
            do {
                system("cls");
            } while (CashierUI());
        }
    }
    cout << "End";
    return 0;
}
