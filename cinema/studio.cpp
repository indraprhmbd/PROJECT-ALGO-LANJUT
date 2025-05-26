#include "studio.h"
#include "movie.h"
#include <iostream>
using namespace std;

void UpdateSession() {
    int studio, session;
    cout << "Which Studio (1-3): ";
    cin >> studio;
    cout << "Which Session (1-5): ";
    cin >> session;
    cout << "Available Movies:\n";
    for (int i = 0; i < CountMovie; i++) {
        cout << i + 1 << ". " << movie[i].title << endl;
    }
    int newMovie;
    cout << "Select Movie: ";
    cin >> newMovie;
    cout << "Session updated!\n";
}

void UpdateTime() {
    int studio, session;
    string newTime;
    cout << "Which Studio (1-3): ";
    cin >> studio;
    cout << "Which Session (1-5): ";
    cin >> session;
    cout << "New Time: ";
    cin >> newTime;
    cout << "Time updated!\n";
}
