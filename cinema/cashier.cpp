#include "cashier.h"
#include "movie.h"
#include "studio.h"
#include "utils.h"
#include <iostream>
#include <sstream>
using namespace std;

bool CashierUI() {
    ShowsMovie();
    int movieIndex;
    cout << "\nChoose a movie (1-" << CountMovie << "): ";
    cin >> movieIndex;
    movieIndex--;

    int studio = 1;
    string time = "14:00";
    string seat;
    cout << "Enter seat (e.g. B2): ";
    cin >> seat;

    stringstream ss;
    ss << "Movie: " << movie[movieIndex].title << "\n"
       << "Studio: " << studio << "\n"
       << "Time: " << time << "\n"
       << "Seat: " << seat << "\n"
       << "Price: Rp 25000\n"
       << "------------------------";
    appendTicketToFile(ss.str());

    cout << "\nTicket booked and saved to history.\n";
    system("pause");
    return true;
}