#include "movie.h"
#include <iostream>
#include <iomanip>

Movie movie[5] = {
    {"Spiderman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"Superman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"Batman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"BonoMan", "Bono", "Action", "20 may 2025", "2h 37m"}
};
int CountMovie = 4;

void ShowsMovie() {
    cout << setw(102) << setfill('-') << "-" << endl;
    cout << "|TITTLE            |PRODUCER            |Genre             |RELEASE DATE        |DURATION            |\n";
    for (int i = 0; i < CountMovie; i++) {
        cout << setw(102) << setfill('-') << "-" << endl;
        cout << setfill(' ');
        cout << "|" << setw(18) << left << movie[i].title
             << "|" << setw(20) << left << movie[i].producer
             << "|" << setw(18) << left << movie[i].genre
             << "|" << setw(20) << left << movie[i].release_d
             << "|" << setw(20) << left << movie[i].duration
             << "|" << '\n';
    }
    cout << setw(102) << setfill('-') << "-" << endl;
}

void CreateMovie() {
    int inputmovieC;
    cout << "How many movies you want to input = "; 
    while (!(cin >> inputmovieC) || inputmovieC <= 0) {
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear(); cin.ignore();
    }
    if (CountMovie + inputmovieC > 5) {
        cout << "Error: Movie storage is full! You can only add " << 5 - CountMovie << " more movies.\n";
        return;
    }
    cin.ignore();
    for (int i = CountMovie; i < inputmovieC + CountMovie; i++) {
        cout << "\n== Movie " << i + 1 << " ==\n";
        cout << "Title\t\t: "; getline(cin, movie[i].title);
        cout << "Genre\t\t: "; getline(cin, movie[i].genre);
        cout << "Producer\t: "; getline(cin, movie[i].producer);
        cout << "Release Date\t: "; getline(cin, movie[i].release_d);
        cout << "Duration\t: "; getline(cin, movie[i].duration);
    }
    CountMovie += inputmovieC;
    cout << "\n" << inputmovieC << " movies successfully added!\n";
}

void UpdateMovie() {
    int choiceMovie;
    ShowsMovie();
    cout << "pilih film ";
    while (!(cin >> choiceMovie) || choiceMovie < 1 || choiceMovie > CountMovie) {
        cout << "Invalid input! Please enter a valid number(1-" << CountMovie << ")";
        cin.clear(); cin.ignore();
    }
    cout << "\n== Movie " << choiceMovie << " ==\n";
    choiceMovie -= 1;
    cin.ignore();
    cout << "Title\t\t: "; getline(cin, movie[choiceMovie].title);
    cout << "Genre\t\t: "; getline(cin, movie[choiceMovie].genre);
    cout << "Producer\t: "; getline(cin, movie[choiceMovie].producer);
    cout << "Release Date\t: "; getline(cin, movie[choiceMovie].release_d);
    cout << "Duration\t: "; getline(cin, movie[choiceMovie].duration);
}