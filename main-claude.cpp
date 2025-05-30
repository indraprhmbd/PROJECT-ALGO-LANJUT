#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

const int MAX_MOVIES = 5;
const int MAX_CASHIERS = 20;
const int MAX_TICKETS = 100;
const int MAX_SESSIONS = 15;
const int MAX_TEMP_BOOKINGS = 100;
const int STUDIOS = 3;
const int SESSIONS_PER_STUDIO = 5;
const int ROWS = 10;
const int COLS = 9;
const int TICKET_PRICE = 25000;

int bookedSeats = 0;
int cashierCount = 0;
string history_filename = "history.txt";
string cashier_filename = "cashier.txt";

string admin[2] = {"admin", "admin123"};
string cashierUser[MAX_CASHIERS];
string cashierPass[MAX_CASHIERS];

struct Movie {
    string title;
    string producer;
    string genre;
    string release_d;
    string duration;
};

Movie movie[MAX_MOVIES] = {
    {"Spiderman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"Superman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"Batman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"BonoMan", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"", "", "", "", ""}
};

int CountMovie = 4;

struct Session {
    bool seat[ROWS][COLS];
    int movie;
    string time;
    
    Session() : movie(0), time("") {
        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                seat[i][j] = false;
            }
        }
    }
};

struct Studio {
    Session session[SESSIONS_PER_STUDIO];
};

Studio studio[STUDIOS];

struct Ticket {
    string title;
    string session;
    string seat;
    
    Ticket() : title(""), session(""), seat("") {}
};
Ticket ticket[MAX_TICKETS];

struct SessionInfo {
    int studioIndex;
    int sessionIndex;
    string time;
    
    SessionInfo() : studioIndex(-1), sessionIndex(-1), time("") {}
};
SessionInfo foundSessions[MAX_SESSIONS];

struct Temporary {
    int tFilm;
    int tStudio;
    int tSesi;
    string tSeat;
    
    Temporary() : tFilm(-1), tStudio(-1), tSesi(-1), tSeat("") {}
};
Temporary temp[MAX_TEMP_BOOKINGS];

int TbookedSeat = 0;

void initializeStudios() {
    // Studio 1
    studio[0].session[0].movie = 0; studio[0].session[0].time = "10:30";
    studio[0].session[1].movie = 0; studio[0].session[1].time = "13:00";
    studio[0].session[2].movie = 0; studio[0].session[2].time = "15:30";
    studio[0].session[3].movie = 0; studio[0].session[3].time = "18:00";
    studio[0].session[4].movie = 0; studio[0].session[4].time = "20:30";

    // Studio 2
    studio[1].session[0].movie = 1; studio[1].session[0].time = "11:00";
    studio[1].session[1].movie = 1; studio[1].session[1].time = "14:00";
    studio[1].session[2].movie = 1; studio[1].session[2].time = "16:30";
    studio[1].session[3].movie = 1; studio[1].session[3].time = "19:00";
    studio[1].session[4].movie = 1; studio[1].session[4].time = "21:30";

    // Studio 3
    studio[2].session[0].movie = 2; studio[2].session[0].time = "10:00";
    studio[2].session[1].movie = 2; studio[2].session[1].time = "12:30";
    studio[2].session[2].movie = 1; studio[2].session[2].time = "15:00";
    studio[2].session[3].movie = 2; studio[2].session[3].time = "17:30";
    studio[2].session[4].movie = 3; studio[2].session[4].time = "20:00";

    // Initialize all seats to false
    for(int s = 0; s < STUDIOS; s++) {
        for(int se = 0; se < SESSIONS_PER_STUDIO; se++) {
            for(int r = 0; r < ROWS; r++) {
                for(int c = 0; c < COLS; c++) {
                    studio[s].session[se].seat[r][c] = false;
                }
            }
        }
    }
}


void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidIntInput(int min, int max, const string& prompt) {
    int input;
    while(true) {
        cout << prompt;
        if(cin >> input && input >= min && input <= max) {
            clearInputBuffer();
            return input;
        }
        cout << "Invalid input! Please enter a number between " << min << " and " << max << endl;
        clearInputBuffer();
    }
}

void loadCashiersFromFile() {
    string filename = cashier_filename;
    ifstream file(cashier_filename);
    if (!file.is_open()) {
        cout << "Warning: Could not open " << filename << ". No cashiers loaded." << endl;
        return;
    }

    string line;
    cashierCount = 0;
    
    while (getline(file, line) && cashierCount < MAX_CASHIERS) {
        istringstream iss(line);
        string user, pass;
        
        if (iss >> user >> pass) {
            cashierUser[cashierCount] = user;
            cashierPass[cashierCount] = pass;
            cashierCount++;
        }
    }
    file.close();
}

void loadHistoryFromFile() {
    ifstream read(history_filename);
    if (!read.is_open()) {
        cout << "Warning: Could not open " << history_filename << ". No history loaded." << endl;
        return;
    }

    string line;
    bookedSeats = 0;

    while (getline(read, line) && bookedSeats < MAX_TICKETS) {
        istringstream ss(line);
        string hTitle, hSession, hSeat;
        
        if (getline(ss, hTitle, '|') && 
            getline(ss, hSession, '|') && 
            getline(ss, hSeat, '|')) {
            
            ticket[bookedSeats].title = hTitle;
            ticket[bookedSeats].session = hSession;
            ticket[bookedSeats].seat = hSeat;
            bookedSeats++;
        }
    }
    read.close();
}

void ShowsMovie() {
    cout << setw(102) << setfill('-') << "-" << endl;
    cout << "|TITLE            |PRODUCER            |GENRE             |RELEASE DATE        |DURATION            |" << endl;
    
    for(int i = 0; i < CountMovie; i++) {
        cout << setw(102) << setfill('-') << "-" << endl;
        cout << setfill(' ');
        cout << "|" << setw(18) << left << movie[i].title
             << "|" << setw(20) << left << movie[i].producer
             << "|" << setw(18) << left << movie[i].genre
             << "|" << setw(20) << left << movie[i].release_d
             << "|" << setw(20) << left << movie[i].duration
             << "|" << endl;
    }
    cout << setw(102) << setfill('-') << "-" << endl;
}

bool ChooseMovie() {
    int film;
    ShowsMovie();
    cout << "(0) for cancel" << endl;
    
    film = getValidIntInput(0, CountMovie, "Pilih Movie : ");
    
    if(film == 0) return false;
    
    temp[0].tFilm = film - 1;
    return true;
}

void ShowSesi() {
    int film = temp[0].tFilm;
    int foundCount = 0;

    // Search for sessions showing the selected movie
    for (int i = 0; i < STUDIOS && foundCount < MAX_SESSIONS; i++) {
        for (int j = 0; j < SESSIONS_PER_STUDIO && foundCount < MAX_SESSIONS; j++) {
            if (studio[i].session[j].movie == film) {
                foundSessions[foundCount].studioIndex = i;
                foundSessions[foundCount].sessionIndex = j;
                foundSessions[foundCount].time = studio[i].session[j].time;
                foundCount++;
            }
        }
    }

    if (foundCount == 0) {
        cout << "Tidak ada sesi yang menayangkan film tersebut." << endl;
        return;
    }
    
    cout << "Sesi yang menayangkan " << movie[film].title << ":" << endl;
    for (int i = 0; i < foundCount; i++) {
        cout << i + 1 << ". " << foundSessions[i].time << endl;
    }
    cout << "0. Back" << endl << endl;
}

bool ChooseSession() {
    ShowSesi();
    
    // Count available sessions first
    int film = temp[0].tFilm;
    int foundCount = 0;
    
    for (int i = 0; i < STUDIOS; i++) {
        for (int j = 0; j < SESSIONS_PER_STUDIO; j++) {
            if (studio[i].session[j].movie == film) {
                foundCount++;
            }
        }
    }
    
    if (foundCount == 0) {
        cout << "No sessions available for this movie." << endl;
        return false;
    }
    
    int pilih = getValidIntInput(0, foundCount, "Pilih sesi film : ");
    
    if(pilih == 0) return false;
    
    temp[0].tSesi = foundSessions[pilih-1].sessionIndex;
    temp[0].tStudio = foundSessions[pilih-1].studioIndex;
    return true;
}

void displaySeats() {
    cout << "   ";
    for(int j = 1; j <= COLS; j++) {
        cout << setw(4) << j;
    }
    cout << endl;
    
    for (int i = 0; i < ROWS; i++) {
        cout << char('A' + i) << "  ";
        for(int j = 0; j < COLS; j++) {
            bool* seatPtr = &studio[temp[0].tStudio].session[temp[0].tSesi].seat[i][j];
            if(*seatPtr == false) {
                cout << setw(4) << "[ ]";
            } else {
                cout << setw(4) << "[X]";
            }
        }
        cout << endl;
    }
    cout << endl << "0. Back" << endl << endl;
}

int seatChecking(const string& seat, int studioIndex, int sessionIndex) {
    if (seat.length() != 2 || !isalpha(seat[0]) || !isdigit(seat[1])) {
        cout << "Invalid seat format! Use format like A1." << endl;
        return -1;
    }

    char rowChar = toupper(seat[0]);
    int rowIndex = rowChar - 'A';
    int colIndex = seat[1] - '1';

    if (rowIndex < 0 || rowIndex >= ROWS || colIndex < 0 || colIndex >= COLS) {
        cout << "Invalid seat! Seat is out of range." << endl;
        return -1;
    }

    bool* seatPtr = &studio[studioIndex].session[sessionIndex].seat[rowIndex][colIndex];
    if (*seatPtr) {
        cout << "This seat is already occupied!" << endl;
        return -1;
    }

    return 0; // Valid seat, don't mark it yet
}

void ticketToFile(const string& title, const string& session, const string& seat) {
    ofstream output(history_filename, ios::app);
    if(!output.is_open()) {
        cout << "Error: Failed to save ticket to " << history_filename << endl;    
        return;
    }
    output << title << "|" << session << "|" << seat << endl;
    output.close();
}

void PrintTicket() {
    int payment;
    int total = TbookedSeat * TICKET_PRICE;

    system("cls");

    int width = 38;
    string separator = string(width, '=');
    string title = "ITIX";

    int leftPadding = (width - 2 - title.length()) / 2;
    int rightPadding = (width - 2) - title.length() - leftPadding;

    cout << "\t\t\t" << separator << endl;
    cout << "\t\t\t|"
         << string(leftPadding, ' ') << title << string(rightPadding, ' ')
         << "|" << endl;
    cout << "\t\t\t" << separator << endl;
    cout << "\t\t\t| Ticket  : "
         << left << setw(width - 12) << setfill(' ') << TbookedSeat << "|" << endl;
    cout << "\t\t\t| Total   : Rp "
         << left << setw(width - 15) << setfill(' ') << total << "|" << endl;
    cout << "\t\t\t" << separator << endl << endl;
 
    do {
        payment = getValidIntInput(0, INT_MAX, "Input Payment : Rp ");
        
        if (payment >= total) {
            cout << "Change : Rp " << (payment - total) << endl;
            break;
        } else {
            cout << "Not enough money!" << endl;
        }
    } while (true);

    // Now mark seats as booked and print tickets
    for (int i = 0; i < TbookedSeat; i++) {
        // Mark seat as booked
        string seat = temp[i].tSeat;
        char rowChar = toupper(seat[0]);
        int rowIndex = rowChar - 'A';
        int colIndex = seat[1] - '1';
        studio[temp[i].tStudio].session[temp[i].tSesi].seat[rowIndex][colIndex] = true;
        
        cout << endl;
        cout << "\t\t\t" << string(38, ' ') << endl; // Blank top border
        cout << "\t\t\t| " << setw(34) << left << "ITIX" << " |" << endl;
        cout << "\t\t\t" << string(38, '=') << endl;

        cout << "\t\t\t| " << setw(34) << left << movie[temp[i].tFilm].title << " |" << endl;

        cout << "\t\t\t| Time    : " 
            << setw(24) << left 
            << studio[temp[i].tStudio].session[temp[i].tSesi].time 
            << " |" << endl;

        cout << "\t\t\t| Studio  : " 
            << setw(24) << left 
            << temp[i].tStudio + 1 
            << " |" << endl;

        // Build seat line as a single string first
        ostringstream seatInfo;
        seatInfo << "Seat " << temp[i].tSeat[0] << " - Row " << temp[i].tSeat[1];

        cout << "\t\t\t| Seat    : " 
            << setw(24) << left << seatInfo.str() 
            << " |" << endl;

        cout << "\t\t\t| " << setw(34) << left << "Rp 25.000" << " |" << endl;
        cout << "\t\t\t" << string(38, '=') << endl;


        ticketToFile(movie[temp[i].tFilm].title, 
                     studio[temp[i].tStudio].session[temp[i].tSesi].time, 
                     temp[i].tSeat);
    }

    // Copy from temp[] to ticket[] with proper data
    for (int i = 0; i < TbookedSeat && (bookedSeats + i) < MAX_TICKETS; i++) {
        ticket[bookedSeats + i].title = movie[temp[i].tFilm].title;
        ticket[bookedSeats + i].session = studio[temp[i].tStudio].session[temp[i].tSesi].time;
        ticket[bookedSeats + i].seat = temp[i].tSeat;
    }

    bookedSeats += TbookedSeat;
    TbookedSeat = 0;
    
    // Clear temp array
    for(int i = 0; i < MAX_TEMP_BOOKINGS; i++) {
        temp[i] = Temporary();
    }
}

bool ChooseSeats() {
    int selectedFilm = temp[0].tFilm;
    int selectedStudio = temp[0].tStudio;
    int selectedSession = temp[0].tSesi;

    cout << "Booking Ticket" << endl;
    displaySeats();

    cout << "\t" << movie[selectedFilm].title 
         << " | " << studio[selectedStudio].session[selectedSession].time << endl << endl;

    int maxSeats = ROWS * COLS;
    int qty = getValidIntInput(1, maxSeats, "Pesan berapa tiket : ");

    if (qty <= 0) return false;

    // Validate all seats first before booking any
    string* seatInputs = new string[qty];
    bool allValid = true;
    
    for (int i = 0; i < qty; i++) {
        cout << "Masukkan Seat " << (i+1) << " (A1-J9) : ";
        cin >> seatInputs[i];
        
        // Convert to uppercase
        if(seatInputs[i].length() >= 1) {
            seatInputs[i][0] = toupper(seatInputs[i][0]);
        }
        
        if (seatChecking(seatInputs[i], selectedStudio, selectedSession) == -1) {
            cout << "Invalid seat: " << seatInputs[i] << endl;
            allValid = false;
            break;
        }
        
        // Check for duplicate seats in current booking
        for(int j = 0; j < i; j++) {
            if(seatInputs[i] == seatInputs[j]) {
                cout << "Duplicate seat selected: " << seatInputs[i] << endl;
                allValid = false;
                break;
            }
        }
        if(!allValid) break;
    }
    
    if(!allValid) {
        delete[] seatInputs;
        return false;
    }
    
    // All seats are valid, save booking info
    TbookedSeat = qty;
    for (int i = 0; i < qty; i++) {
        temp[i].tFilm = selectedFilm;
        temp[i].tStudio = selectedStudio;
        temp[i].tSesi = selectedSession;
        temp[i].tSeat = seatInputs[i];
    }
    
    delete[] seatInputs;
    
    PrintTicket();
    cout << endl;
    system("pause");
    return true;
}

void CreateMovie() {
    int inputmovieC = getValidIntInput(1, MAX_MOVIES - CountMovie, 
        "How many movies you want to input = ");

    if (CountMovie + inputmovieC > MAX_MOVIES) {
        cout << "Error: Movie storage is full! You can only add " 
             << MAX_MOVIES - CountMovie << " more movies." << endl;
        return;
    }

    clearInputBuffer();

    for(int i = CountMovie; i < inputmovieC + CountMovie; i++) {
        cout << "\n== Movie " << i + 1 << " ==" << endl;
 
        cout << "Title\t\t: "; 
        getline(cin, movie[i].title);
        cout << "Genre\t\t: ";
        getline(cin, movie[i].genre);
        cout << "Producer\t: ";
        getline(cin, movie[i].producer);
        cout << "Release Date\t: ";
        getline(cin, movie[i].release_d);
        cout << "Duration\t: ";
        getline(cin, movie[i].duration);
    }

    CountMovie += inputmovieC;
    cout << "\n" << inputmovieC << " movies successfully added!" << endl;
}

void UpdateMovie() {
    ShowsMovie();
    
    int choiceMovie = getValidIntInput(1, CountMovie, "Pilih film : ");
    choiceMovie -= 1;
    
    cout << "\n== Movie " << choiceMovie + 1 << " ==" << endl;
    
    clearInputBuffer();
    cout << "Title\t\t: "; 
    getline(cin, movie[choiceMovie].title);
    cout << "Genre\t\t: ";
    getline(cin, movie[choiceMovie].genre);
    cout << "Producer\t: ";
    getline(cin, movie[choiceMovie].producer);
    cout << "Release Date\t: ";
    getline(cin, movie[choiceMovie].release_d);
    cout << "Duration\t: ";
    getline(cin, movie[choiceMovie].duration);
    
    cout << "Movie updated successfully!" << endl;
}

void UpdateSession() {
    int choiceSt = getValidIntInput(1, STUDIOS, "Which Studio (1-3): ");
    int choiceSS = getValidIntInput(1, SESSIONS_PER_STUDIO, "Which Session (1-5): ");

    choiceSt--; 
    choiceSS--; 

    int currentMovie = studio[choiceSt].session[choiceSS].movie;
    cout << "\nCurrent movie in session: " << movie[currentMovie].title << endl;

    cout << "\nChoose new movie:" << endl;
    for (int i = 0; i < CountMovie; i++) {
        cout << i + 1 << ". " << movie[i].title << endl;
    }

    int newMovie = getValidIntInput(1, CountMovie, "Enter new movie number: ");

    studio[choiceSt].session[choiceSS].movie = newMovie - 1;
    cout << "Session updated! New movie: " << movie[newMovie - 1].title << endl;
}

void UpdateTime() {
    int choiceSt = getValidIntInput(1, STUDIOS, "Which Studio (1-3): ");
    choiceSt--;
    
    cout << "Current session times:" << endl;
    for(int i = 0; i < SESSIONS_PER_STUDIO; i++) {
        cout << i + 1 << ". " << studio[choiceSt].session[i].time << endl;
    }

    int choiceSS = getValidIntInput(1, SESSIONS_PER_STUDIO, "Which Session (1-5): ");
    choiceSS--;

    string newTime;
    cout << "Enter new time: ";
    clearInputBuffer();
    getline(cin, newTime);
    
    studio[choiceSt].session[choiceSS].time = newTime;
    cout << "Time updated! New Session: " << studio[choiceSt].session[choiceSS].time << endl;
}

bool cashierCheck(const string& user, const string& pass) {
    for(int i = 0; i < cashierCount; i++) {
        if(user == cashierUser[i] && pass == cashierPass[i]) {
            return true;
        }
    }
    return false;
}   

int partition(int low, int high, int mode) {
    string pivot;
    switch (mode) {
        case 0: pivot = ticket[high].title; break;
        case 1: pivot = ticket[high].session; break;
        case 2: pivot = ticket[high].seat; break;
        default: pivot = ticket[high].title; break;
    }

    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool condition = false;

        switch (mode) {
            case 0: condition = ticket[j].title < pivot; break;
            case 1: condition = ticket[j].session < pivot; break;
            case 2: condition = ticket[j].seat < pivot; break;
            default: condition = ticket[j].title < pivot; break;
        }

        if (condition) {
            i++;
            swap(ticket[i], ticket[j]);
        }
    }

    swap(ticket[i + 1], ticket[high]);
    return i + 1;
}

void quicksortTickets(int low, int high, int mode) {
    if (low < high) {
        int pi = partition(low, high, mode);
        quicksortTickets(low, pi - 1, mode);
        quicksortTickets(pi + 1, high, mode);
    }
}

void sortTicketsBy(int mode) {
    if (bookedSeats == 0) {
        cout << "No tickets to sort." << endl;
        return;
    }

    quicksortTickets(0, bookedSeats - 1, mode);
    string field = (mode == 0) ? "title" : (mode == 1) ? "session" : "seat";
    cout << "Tickets sorted by " << field << "." << endl;
}

bool login(bool &is_admin) {
    string user, pass;
    is_admin = false;
    
    for(int attempts = 3; attempts > 0; attempts--) {
        system("cls");
        cout << "== LOGIN ==" << endl;
        cout << "Username \t: "; cin >> user;
        cout << "Password \t: "; cin >> pass;

        if(user == admin[0] && pass == admin[1]) {
            is_admin = true;
            return true;
        }
        else if(cashierCheck(user, pass)) {
            system("cls");
            cout << "Welcome! ";
            for(char c : user) {
                cout << (char)toupper(c);
            }
            cout << "!" << endl;
            system("pause");
            return true;
        }
        
        if(attempts > 1) {
            cout << "Username or Password wrong! Tries remaining: " << (attempts - 1) << endl;
            system("pause");
        }
    }
    return false;
}

void showData() {
    if(bookedSeats == 0) {
        cout << "No tickets found." << endl;
        return;
    }
    
    for(int i = 0; i < bookedSeats; i++) {
        cout << "Movie : " << ticket[i].title 
             << ", Session : " << ticket[i].session 
             << ", Seat : " << ticket[i].seat << endl;
    }
    cout << endl;
}

void historyList() {
    while(true) {
        system("cls");
        cout << string(30,'=') << endl 
             << "HISTORY" << endl 
             << string(30,'=') << endl;
        showData();
        cout << "1. Sort by Title" << endl;
        cout << "2. Sort by Session" << endl;
        cout << "3. Sort by Seat" << endl;
        cout << "4. Back" << endl;
        
        int hChoose = getValidIntInput(1, 4, "Choose : ");

        switch(hChoose) {
            case 1: 
                sortTicketsBy(0);
                system("pause");
                break;
            case 2: 
                sortTicketsBy(1);
                system("pause");
                break;
            case 3: 
                sortTicketsBy(2);
                system("pause");
                break;
            case 4: 
                return;
        }
    }
}

void registerNewCashier(){
    int qty;
    string newUser, newPass;

    cout << "Register New Cashier " << endl;

    if(cashierCount == MAX_CASHIERS){
        cout<<"Sorry, u can't add more cashier"<<endl;
        return;
    }
    cout<< "How many : "; cin>>qty;

    clearInputBuffer();

    
    for(int i=cashierCount;i<cashierCount+qty;i++){
        cout<<string(10,'-')<<endl;
        cout<<i+1<<".Username : "; getline(cin,cashierUser[i]);
        cout<<"password : "; getline(cin,cashierPass[i]);
    }

    cashierCount += qty;

    char inputCheck;
    cout<<"That's all? (y/n): ";cin>>inputCheck;
    if(inputCheck=='n') registerNewCashier();
    return;
}

void showCashierList(){
    cout<<endl;
    for(int i = 0 ; i < cashierCount ; i++ ){
        cout<<i+1<<". username : "<<cashierUser[i]
            <<", password : "<<cashierPass[i] << endl;
    }
}

void deleteCashier(){
    cout<<"Delete Cashier Account"<<endl;
    int del_in;
    char inputCheck;

    showCashierList();

    cout<<"Which Cashier do u want to delete? (num): ";cin>>del_in; del_in-=1;
    cout<<"delete : "<<cashierUser[del_in]<<" ? (y/n) : "; cin>>inputCheck;
    if(inputCheck=='y') {
        for(int i=del_in;i<cashierCount;i++){
            cashierUser[i]=cashierUser[i+1];
            cashierPass[i]=cashierPass[i+1];
        }
        cashierCount--;
    }
}

void cashierList(){
    int choose;

    cout<<"Registered cashier(s) : " << endl;
    showCashierList();

    cout<<endl;
    cout<<"1. Register New Cashier" <<endl;
    cout<<"2. Delete Registered Cashier"<<endl;
    cout<<"0. Back"<<endl;
    cout<<"Choose : "; cin >> choose;

    switch(choose){
        case 1 : registerNewCashier(); break;
        case 2 : deleteCashier(); break;
        case 0 : return ;
        default : break;
    }

    showCashierList();

    ofstream cInput(cashier_filename);
    for(int i=0;i<cashierCount;i++){
        cInput << cashierUser[i] << " " << cashierPass[i] << endl;
    }
    cInput.close();
}

bool AdminUI() {
    cout<<"ADMIN MENU : "<<endl;
    cout << "1. Show Movie" << endl;
    cout << "2. Create Movie" << endl;
    cout << "3. Update Movie" << endl;
    cout << "4. Update Session" << endl;
    cout << "5. Update Time" << endl;
    cout << "6. History List" << endl;
    cout << "7. Register/Delete Cashier" << endl;
    cout << "8. Logout" << endl;
    
    int pilih = getValidIntInput(1, 8, "Pilih : ");
    system("cls");
    
    switch (pilih) {
        case 1: ShowsMovie(); break;
        case 2: CreateMovie(); break;
        case 3: UpdateMovie(); break;
        case 4: UpdateSession(); break;
        case 5: UpdateTime(); break;
        case 6: historyList(); return true; 
        case 7: cashierList(); break;
        case 8: return false;
    }
    system("pause");
    return true;
}

bool CashierUI() {
    cout<<"CASHIER MENU : " << endl;
    cout << "1. Show Movie" << endl;
    cout << "2. Pesan Ticket" << endl;
    cout << "3. Logout" << endl;
    
    int pilih = getValidIntInput(1, 3, "Pilih : ");
    system("cls");
    
    switch (pilih) {
        case 1:
            ShowsMovie();
            break;
        case 2:
            while(ChooseMovie()) {
                while(ChooseSession()) {
                    if(ChooseSeats()) {
                        return true;
                    }
                    system("cls");
                }
                system("cls");
            }
            break;
        case 3:
            return false;
    }
    system("pause");
    return true;
}

int main() {
    initializeStudios();
    loadCashiersFromFile();
    loadHistoryFromFile();
    
    bool is_admin;
    while(login(is_admin)) {
        if(is_admin) {
            do {
                system("cls");
            } while(AdminUI());
        } else {
            do {
                system("cls");
            } while(CashierUI());
        }
    }
    
    cout << "Program ended. Thank you!" << endl;
    return 0;
}