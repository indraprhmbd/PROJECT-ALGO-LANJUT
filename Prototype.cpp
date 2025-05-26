#include <iostream>
#include <cstdio>      // fopen, fgets, sscanf
#include <cstring>     // strlen
#include <vector>
#include <string>
using namespace std;
vector<string> cashierUser;
vector<string> cashierPass;

string admin[2][1] = {{"admin"}, {"admin123"}};

void loadCashiersFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char user[50], pass[50];
        if (sscanf(line, "%s %s", user, pass) == 2) {
            cashierUser.push_back(string(user));
            cashierPass.push_back(string(pass));
        }
    }
    fclose(file);
}

struct Studio {
    char studioNum;
};

struct Session {
    string time;
    bool seats[10][9];
};

struct Movie {
    string title;
    string producer;
};

struct BookedTicket {
    int movieIndex;
    int sessionIndex;
    int studioIndex;
    string bookedSeat;
};

Studio studio[3] = { {'1'},{'2'},{'3'} };

Session session[3] = {
    {"12.00",false},
    {"14.30",false},
    {"16.30",false}
};

Movie movie[5]= {
    {"Movie 1","Indra"},
    {"Movie 2","Indra2"},
    {"Movie 3","Indra3"},
    {"Movie 4","Indra4"},
    {"Movie 5","Indra5"}
};

Movie* movies = movie; 

BookedTicket ticket[200];
long bookedSeats=0;

bool cashierCheck(string user,string pass){
    bool u=false,p=false;
    for(int i=0;i<cashierUser.size();i++){
        if(user == cashierUser[i]) u=true;
    }
    for(int i=0;i<cashierPass.size();i++){   
        if(pass == cashierPass[i]) p=true;
    }
    return u && p;
}   

bool login(bool &admin){
    string user,pass;
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
                cout<<char(toupper(s))<<" ";
            }
            cout<<"!"<<endl;
            return true;
        }
        cout<<"Username or Password wrong! Try Remaining : "<<i<<endl;
        system("pause");
    }
    return false;
}

void inputMovie(){
    int N;
    char verify;
    string mov;
    cout<<"Input Film"<<endl;
    cout<<"Berapa banyak? (max 5): "; cin>>N;
    if(N>5 || N<1) cout<<"Unaccepted! Try again later"<<endl;
    else {
        for(int i=0;i<N;i++){
            cout<<"INPUT MOVIE ["<<i+1<<"]"<<endl;
            cout<<"Title : ";cin.ignore();getline(cin,movie[i].title);
            cout<<"Producer : ";getline(cin,movie[i].producer);
            cout<<"Is it all correct? (y/n) : ";cin>>verify;
            if(verify!='y') i--;
        }
    }
}

void displaySeats(){
    for (int i = 0; i < 10; i++) {
        for(int j=0;j<9;j++){
            cout << "       " << char('A' + i) << j + 1; // Tampilan kursi kosong
        }
        cout << "\n\n";
    }
}

int choosingMovieSession(int A){
    int choice,N;
    if(A==1) {
        N=sizeof(movies)/sizeof(movies[0]);
        cout<<"== Choose a movie =="<<endl;
    } else if(A==2) {
        N=sizeof(session)/sizeof(session[0]);
        cout<<"== Choose a session =="<<endl;
    }

    for(int i=0;i<N;i++){
        if(A==1){
            cout<<i+1<<". "<<movies[i].title<<endl;
        } else if(A==2){
            cout<<i+1<<". "<<session[i].time<<endl;
        }
    }
    cout<<"Choose : ";cin>>choice;
    return choice-1;
}

int seatChecking(string &seat,int mov,int ses){
    
    if(seat[0]>90) seat[0]-=32;
    
    int rowIndex=seat[0] - 'A';
    int colIndex=seat[1] - '1';
    bool s_check=session[ses].seats[rowIndex][colIndex];

    if(s_check==false && rowIndex<10 && colIndex<9 && seat.length()==2){
        cout<<"seat "<<seat[0]<<seat[1]<<" booked successfully!"<<endl;
        session[ses].seats[rowIndex][colIndex]=true;
        return 0;
    }else if(s_check==true)
        cout<<"This seat is occupied!"<<endl;
    else {
        cout<<"Invalid seat! please try again"<<endl;
    }
    return -1;
}

int bookingTicket(){
    int qty;
    string seat;
    cout<<"Booking Ticket"<<endl;
    int Mov=choosingMovieSession(1);
    int Ses=choosingMovieSession(2);

    system("cls");
    displaySeats();
    cout<<"\t"<<movie[Mov].title<<" | "<<session[Ses].time<<endl<<endl;

    cout<<"How much seat(s) do you want to book? :";cin>>qty;
    for(int i=bookedSeats;i<bookedSeats+qty;i++){
        ticket[i].movieIndex = Mov;
        ticket[i].sessionIndex = Ses;
        cout<<"Masukkan Seat (A1-J9) : ";cin>>seat;
        if(seatChecking(seat,Mov,Ses)==-1) i--;
        else ticket[i].bookedSeat=seat;
    }
    bookedSeats+=qty;
    return 0;
}

void ticketHistory(int i){
    if(i==bookedSeats) return;

    int mov = ticket[i].movieIndex;
    int ses = ticket[i].sessionIndex;
    int studio = ticket[i].studioIndex;
    string seatNum=ticket[i].bookedSeat;
    
    cout<<i+1
    <<". Movie: "<<movie[mov].title
    <<", Session: "<<session[ses].time
    <<", Seat:"<<seatNum<<endl;
    ticketHistory(i+1);
}   

void sortHistory(){
    int TempMovie, TempSession, TempStudio;
    string TempSeat;
    for(int i=0;i<bookedSeats-1;i++){
        for (int j=0;j<bookedSeats-i-1; j++){
            if(ticket[j].movieIndex > ticket[j+1].movieIndex){
                TempMovie = ticket[j].movieIndex;
                TempSession = ticket[j].sessionIndex;
                TempStudio = ticket[j].studioIndex;
                TempSeat = ticket[j].bookedSeat;
                ticket[j].movieIndex = ticket[j+1].movieIndex;
                ticket[j].sessionIndex = ticket[j+1].sessionIndex;
                ticket[j].studioIndex = ticket[j+1].studioIndex;
                ticket[j+1].bookedSeat = ticket[j+1].bookedSeat;
                ticket[j+1].movieIndex = TempMovie;
                ticket[j+1].sessionIndex = TempSession;
                ticket[j+1].studioIndex = TempStudio;
                ticket[j+1].bookedSeat = TempSeat;
            }
        }
    }
    ticketHistory(0);
    system("pause");
}

int main(){
    char ulang;
    do{ 
        system("cls");
        ulang='n';
        bool admin=false;

        // Load data kasir dari file
        loadCashiersFromFile("cashiers.txt");

        if(login(admin)){
            char menu;
            cout<<"login berhasil!"<<endl;
            system("pause");
            system("cls");
            do{
                cout<<"Main menu"<<endl;
                if (admin) 
                    cout<<"#.    Input Film (admin)"<<endl;

                cout<<"1.   Booking Tickets "<<endl;
                cout<<"2.   History "<<endl;
                cout<<"3.   Back"<<endl;
                cout<<"Choose : "; cin>>menu;

                if(menu == '#'){
                    inputMovie();
                    system("pause");
                } else if(menu=='1'){
                    bookingTicket();
                    system("pause");
                } else if(menu=='2'){
                    char in;
                    system("cls");
                    cout<<"HISTORY : "<<endl;
                    ticketHistory(0);
                    cout<<"Do you want to sort? (y/n) : ";cin>>in;
                    if(in=='y'){
                        sortHistory();
                    }
                }
            }while(menu!='3');
        } else { 
            cout<<"Login Failed! Please try again."<<endl;
            system("pause");
        }
        cout<<"Do you want to exit ? (y/n) : ";cin>>ulang;
        
    }while(ulang!='y');
}
