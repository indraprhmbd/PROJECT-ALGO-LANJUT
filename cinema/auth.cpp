#include "auth.h"

string cashierUser[4];
string cashierPass[4];

bool cashierCheck(string user, string pass) {
    for (int i = 0; i < 4; i++) {
        if (user == cashierUser[i] && pass == cashierPass[i]) return true;
    }
    return false;
}

void loadCashiersFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char user[50], pass[50];
    int i = 0;
    while (fscanf(file, "%s %s", user, pass) == 2 && i < 4) {
        cashierUser[i] = user;
        cashierPass[i] = pass;
        i++;
    }
    fclose(file);
}

bool login(bool &admin) {
    string user, pass;
    admin = false;
    for (int i = 3; i >= 0; i--) {
        system("cls");
        cout << "== LOGIN ==" << endl;
        cout << "Username\t: "; cin >> user;
        cout << "Password\t: "; cin >> pass;

        if (user == "admin" && pass == "admin123") {
            admin = true;
            return true;
        } else if (cashierCheck(user, pass)) {
            system("cls");
            cout << "Welcome! ";
            for (char s : user) cout << char(toupper(s)) << " ";
            cout << "!" << endl;
            return true;
        }
        cout << "Username or Password wrong! Try Remaining : " << i << endl;
        system("pause");
    }
    return false;
}