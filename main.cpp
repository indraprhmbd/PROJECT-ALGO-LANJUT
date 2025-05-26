#include <iostream>
#include <iomanip>
using namespace std;

int bookedSeats = 0;

string admin[2][1] = {{"admin"}, {"admin123"}};
string cashierUser[4];
string cashierPass[4];

struct Movie{
    string title;
    string producer;
    string genre;
    string release_d;
    string duration;
};

Movie movie[5] = {
    {"Spiderman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"Superman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"Batman", "Bono", "Action", "20 may 2025", "2h 37m"},
    {"BonoMan", "Bono", "Action", "20 may 2025", "2h 37m"}
}; int CountMovie =  4; //buat nyimpen movie(moviecount)

struct Session{
    bool seat[10][9];
    int movie;
    string time;
};

struct Studio{
    Session session[5];
}; 

Studio studio[3] = {
    {{{{false}, 0, "10:30"}, {{false}, 0, "13:00"}, {{false}, 0, "15:30"}, {{false}, 0, "18:00"}, {{false}, 0, "20:30"}}},
    {{{{false}, 1, "11:00"}, {{false}, 1, "14:00"}, {{false}, 1, "16:30"}, {{false}, 1, "19:00"}, {{false}, 1, "21:30"}}},
    {{{{false}, 2, "10:00"}, {{false}, 2, "12:30"}, {{false}, 1, "15:00"}, {{false}, 2, "17:30"}, {{false}, 3, "20:00"}}}
};

struct Ticket{
    int title;
    int session;
    string seat;
}; Ticket ticket[100];

// Struktur untuk menyimpan hasil pencarian
struct SessionInfo {
    int studioIndex;
    int sessionIndex;
    string time;    
}; SessionInfo foundSessions[15]; //Array dengan ukuran maksimum (3 studio × 5 sesi = 15)

struct Temporary {
    int tFilm;
    int tStudio;
    int tSesi;
    string tSeat;
}; Temporary temp[100];

int TbookedSeat = 0;

void loadCashiersFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[100];
    int i=0;
    while (fgets(line, sizeof(line), file)) {
        char user[50], pass[50];
        if (sscanf(line, "%s %s", user, pass) == 2) {
            cashierUser[i]=user;
            cashierPass[i]=pass;
            i++;
        }
    }
    fclose(file);
}

void ShowsMovie(){
    cout<<setw(102)<<setfill('-')<<"-"<<endl;
    cout<<"|TITTLE            |PRODUCER            |Genre             |RELEASE DATE        |DURATION            |\n";
    for(int i = 0; i < CountMovie; i++){
        cout<<setw(102)<<setfill('-')<<"-"<<endl;
        cout<<setfill(' ');
        cout<<"|"<<setw(18)<<left<<movie[i].title
            <<"|"<<setw(20)<<left<<movie[i].producer
            <<"|"<<setw(18)<<left<<movie[i].genre
            <<"|"<<setw(20)<<left<<movie[i].release_d
            <<"|"<<setw(20)<<left<<movie[i].duration
            <<"|"<<'\n';
    }
    cout<<setw(102)<<setfill('-')<<"-"<<endl;
}

bool ChooseMovie(){
    int film;
    ShowsMovie();
    cout << "(0) for cancel\n";
    cout << "Pilih Movie : ";

    while (!(cin >> film) || film < 1 || film > CountMovie) { 
        if(film == 0) return false;
        cout << "Invalid input! Please enter a valid number" << "(1-" << CountMovie << ")" ;
        cin.clear();
        cin.ignore();
    }

    temp[0].tFilm = film-1;
    return true;
}

// Fungsi searchSesi tanpa vector
void ShowSesi() {
    int film = temp[0].tFilm;

    int foundCount = 0; // Penghitung jumlah sesi yang ditemukan

    // Satu kali traversal untuk mencari dan menyimpan
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (studio[i].session[j].movie == film) {
                foundSessions[foundCount].studioIndex = i;
                foundSessions[foundCount].sessionIndex = j;
                foundSessions[foundCount].time = studio[i].session[j].time;
                foundCount++;
            }
        }
    }

    // Tampilkan hasil
    if (foundCount == 0) {
        cout << "Tidak ada sesi yang menayangkan film tersebut." << endl;
    } else {
        cout << "Sesi yang menayangkan " << movie[film].title << ":" << endl;
        for (int i = 0; i < foundCount; i++) {
            cout << i+1 << ". "<< foundSessions[i].time << endl;
        }
        cout << "0. Back\n\n";
    }
}

bool ChooseSession(){
    ShowSesi();
    int pilih;
    
    cout << "Pilih sesi film : "; cin >> pilih;

    if(pilih == 0) return false;

    temp[0].tSesi = foundSessions[pilih-1].sessionIndex;
    temp[0].tStudio = foundSessions[pilih-1].studioIndex;
    return true;
}

void displaySeats(){
    for (int i = 0; i < 10; i++) {
        for(int j=0;j<9;j++){
            if(studio[temp[0].tStudio].session[temp[0].tSesi].seat[i][j] == false){
                cout << "       " << char('A' + i) << j + 1; // Tampilan kursi kosong
            } else if (studio[temp[0].tStudio].session[temp[0].tSesi].seat[i][j] == true){
                cout << "       " << "XX"; // Tampilan kursi terisi
            }
        }
        cout << "\n\n";
    }
    cout << "0. Back\n\n";
}

int seatChecking(string &seat,int mov,int ses){
    
    if(seat[0]>90) {
        seat[0] -= 32;
    }
    int rowIndex = seat[0] - 'A';
    int colIndex = seat[1] - '1';
    
    if (seat.length() != 2 ||
        seat[0] < 'A' || seat[0] > 'J' ||
        seat[1] < '1' || seat[1] > '9') {
        cout << "Invalid seat format! Please use format like A1, B2..." << endl;
        return -1;
    }

    bool s_check = studio[temp[0].tStudio].session[temp[0].tSesi].seat[rowIndex][colIndex];

    if(s_check == false && rowIndex < 10 && colIndex < 9 && seat.length() == 2){
        cout << "seat " << seat[0] << seat[1] << " booked successfully!" << endl;
        studio[temp[0].tStudio].session[temp[0].tSesi].seat[rowIndex][colIndex] = true;
        return 0;
    } else if(s_check == true) {
        cout<<"This seat is occupied!"<<endl;
    } else {
        cout<<"Invalid seat! please try again"<<endl;
    }

    return -1;
}   

void PrintTicket(){

    int payment;
    system("cls");
    cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    cout << endl;
    cout << left << "\t\t\t|" << setfill(' ') << setw(15) << " " << "ITIX" << right << setfill(' ') << setw(17) << "|";
    cout << endl;
    cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    cout << endl;
    cout << "\t\t\t| "<<"Ticket  : " << left << setfill(' ') << setw(24) << TbookedSeat << "|";
    cout << endl;
    cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
    cout << endl;
    cout << "\t\t\t| "<<"Total  : Rp " << left << setfill(' ') << setw(22) << 25000*TbookedSeat << "|";
    cout << endl;
    cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    cout << endl << endl;
    do{
        cout << "Input Payment : Rp ";cin >> payment;
        if(payment >= TbookedSeat*25000){
            cout << "Change : Rp " << payment-(TbookedSeat*25000);
            break;
        } else cout << "Not enough\n";
    } while(true);



    for(int i = 0; i < TbookedSeat; i++){
        cout << endl;
        cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
        cout << endl;
        
        cout << left << "\t\t\t|" << setfill(' ') << setw(15) << " " << "ITIX" << right << setfill(' ') << setw(17) << "|";
        cout << endl;
        
        cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
        cout << endl;
        
        cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
        cout << endl;
        
        cout << "\t\t\t| " << left << setfill(' ') << setw(34) <<  movie[temp[0].tFilm].title << "|";
        cout << endl;
        
        cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
        cout << endl;
        
        cout << "\t\t\t| "<< "Time\t  : " << left << setfill(' ') << setw(24) << studio[temp[0].tStudio].session[temp[0].tSesi].time << "|";
        cout << endl;
        
        cout << "\t\t\t| "<< "Studio  : " << left << setfill(' ') << setw(24) << temp[0].tStudio + 1 << "|";
        cout << endl;
        
        cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
        cout << endl;
        
        cout << "\t\t\t| "<< "Seat\t  : " <<  temp[i].tSeat[0] << "    -    Row  : " << temp[i].tSeat[1] << left << setfill(' ') << setw(6) << " " << "|";
        cout << endl;
        
        cout << "\t\t\t| " << left << setfill(' ') << setw(34) << "Rp 25.000" << "|";
        cout << endl;
        
        cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    }

    for(int i=bookedSeats;i<bookedSeats+TbookedSeat;i++){
        ticket[i].title = temp[i].tFilm;
        ticket[i].session = temp[i].tSesi;
        ticket[i].seat = temp[i].tSeat;
    }
    bookedSeats+=TbookedSeat;
    TbookedSeat = 0;
}

bool ChooseSeats(){
    int qty;
    string seat;
    cout<<"Booking Ticket"<<endl;

    displaySeats();

    cout << "\t" << movie[temp[0].tFilm].title << " | " <<  studio[temp[0].tStudio].session[temp[0].tSesi].time << endl << endl;

    cout << "Pesan berapa ticket : "; cin >> qty;
    
    if(qty == 0) return false;
    
    for(int i=TbookedSeat; i < TbookedSeat+qty; i++){
        int rowIndex = seat[0] - 'A';
        int seatIndex = seat[1] - '1';

        temp[i].tFilm = temp[0].tFilm;
        temp[i].tSesi = temp[0].tSesi;
        temp[i].tStudio = temp[0].tStudio;

        cout<<"Masukkan Seat (A1-J9) : ";cin>>seat;
        if(seatChecking(seat,temp[0].tFilm,temp[0].tSesi) == -1){
            i--;
        } else {
            temp[i].tSeat = seat;
        }
    }
    TbookedSeat += qty;
    PrintTicket();
    cout << endl;
    system("pause");
    return true;
}


void CreateMovie(){
    int inputmovieC;

    cout << "How many movies you want to input = "; 
    while (!(cin >> inputmovieC) || inputmovieC <= 0) { // Validasi input
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear();
        cin.ignore();
    }

    if (CountMovie + inputmovieC > 5) { // Cek batas array
        cout << "Error: Movie storage is full! You can only add " << 5 - CountMovie << " more movies.\n";
        return;
    }

    cin.ignore();

    for(int i = CountMovie;  i < inputmovieC + CountMovie ; i++){
        cout << "\n== Movie " << i + 1 << " ==\n";
 
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

    CountMovie += inputmovieC; // Update jumlah film yang tersimpan
    cout << "\n" << inputmovieC << " movies successfully added!\n";
}

void UpdateMovie(){
    int choiceMovie;

    ShowsMovie();

    cout << "pilih film "; 

    while (!(cin >> choiceMovie) || choiceMovie < 1 || choiceMovie > CountMovie) { 
        cout << "Invalid input! Please enter a valid number" << "(1-" << CountMovie << ")" ;
        cin.clear();
        cin.ignore();
    }

    
    cout << "\n== Movie " << choiceMovie << " ==\n";
    
    choiceMovie -= 1;
    cin.ignore();
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

}

void UpdateSession() {

    int choiceSt, choiceSS;
    cout << "Which Studio (1-3): ";
    while (!(cin >> choiceSt) || choiceSt < 1 || choiceSt > 3) { 
        cout << "Invalid input! Please enter a valid number (1-3): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Which Session (1-5): ";
    while (!(cin >> choiceSS) || choiceSS < 1 || choiceSS > 5) { 
        cout << "Invalid input! Please enter a valid number (1-5): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    choiceSt--; // Ubah ke index array (0-2)
    choiceSS--; // Ubah ke index array (0-4)

    int currentMovie = studio[choiceSt].session[choiceSS].movie;
    cout << "\nCurrent movie in session: " << movie[currentMovie].title << endl;

    cout << "\nChoose new movie (must be different):\n";
    for (int i = 0; i < CountMovie; i++) {
        if (i != currentMovie) {
            cout << i + 1 << ". " << movie[i].title << endl;
        }
    }

    int newMovie;
    while (true) {
        cout << "Enter new movie number: ";
        cin >> newMovie;
        if (newMovie < 1 || newMovie > CountMovie || newMovie - 1 == currentMovie) {
            cout << "Invalid choice! Pick a different movie.\n";
        } else {
            break;
        }
    }

    // Update sesi dengan film baru
    studio[choiceSt].session[choiceSS].movie = newMovie - 1;
    cout << "Session updated! New movie: " << movie[newMovie - 1].title << endl;
}

void UpdateTime(){
    int choiceSt, choiceSS;
    cout << "Which Studio (1-3): ";
    while (!(cin >> choiceSt) || choiceSt < 1 || choiceSt > 3) { 
        cout << "Invalid input! Please enter a valid number (1-3): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    choiceSt--; // Ubah ke index array (0-2)
    
    for(int i = 0; i < 5; i++){
        cout << i+1 << ". " << studio[choiceSt].session[i].time << endl;
    }

    cout << "Which Session (1-5): ";
    while (!(cin >> choiceSS) || choiceSS < 1 || choiceSS > 5) { 
        cout << "Invalid input! Please enter a valid number (1-5): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    choiceSS--; // Ubah ke index array (0-4)

    string newTime;
    string currentTime = studio[choiceSt].session[choiceSS].time;

    while (true) {
        cout << "Enter new time number: ";
        cin >> newTime;
        if (newTime == currentTime) {
            cout << "Invalid choice! Pick a different time.\n";
        } else {
            break;
        }
    }
    studio[choiceSt].session[choiceSS].time = newTime;
    cout << "Time updated! New Session: " <<  studio[choiceSt].session[choiceSS].time << endl;
}

bool cashierCheck(string user,string pass){
    for(int i=0;i<4;i++){
        if(user == cashierUser[i] && pass == cashierPass[i]) return true;
    }
    return false;
}   

bool login(bool &admin){
    string user,pass;
    admin = false;
    for(int i=3;i>=0;i--){
        system("cls");
        cout<<"== LOGIN =="<<endl;
        cout<<"Username \t: ";cin>>user;
        cout<<"Password \t: ";cin>>pass;

        if(user == "admin" && pass == "admin123") {
            admin=true;
            return true;
        }
        else if(cashierCheck(user,pass)) {
            system("cls");
            cout<<"Welcome! ";
            for(char s : user) {
                cout<<char(s-32)<<" ";
            }
            cout<<"!"<<endl;
            return true;
        }
        cout<<"Username or Password wrong! Try Remaining : "<<i<<endl;
        system("pause");
    }
    return false;
}

bool AdminUI(){
    int pilih;
    cout << "1. Show Movie\n";
    cout << "2. Create Movie\n";
    cout << "3. Update Movie\n";
    cout << "4. Update Session\n";
    cout << "5. Update Time\n";
    cout << "6. Logout\n";
    cout << "Pilih : "; cin >> pilih;
    system("cls");
    switch (pilih){
        case 1:
            ShowsMovie();
        break;
        case 2:
            CreateMovie();
        break;
        case 3:
            UpdateMovie();
        break;
        case 4:
            UpdateSession();
        break;
        case 5:
            UpdateTime();
        break;
        case 6:
            return false;
        break;
        
        default:
            break;
    }
    system("pause");
    return true;
}

bool CashierUI(){
    int pilih;
    cout << "1. Show Movie\n";
    cout << "2. Pesan Ticket\n";
    cout << "3. Logout\n";
    cout << "Pilih : "; cin >> pilih;
    system("cls");
    switch (pilih){
        case 1:
            ShowsMovie();
        break;
        case 2:
            while(ChooseMovie()){
                while(ChooseSession()){
                    while(ChooseSeats()){
                        return true;
                    }
                    system("cls");
                }
                system("cls");
            }
        break;
        case 3:
            return false;
        break;
        
        default:
        break;
    }
    system("pause");
    return true;
}

int main(){
    bool admin;
    loadCashiersFromFile("cashiers.txt");
    while(login(admin)){
        if(admin){
            do{
                system("cls");
            } while(AdminUI());
        } else {
            do{
                system("cls");
            } while(CashierUI());
        }
    }
    cout << "End";
}