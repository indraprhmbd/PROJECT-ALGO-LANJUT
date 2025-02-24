#include <iostream>
using namespace std;

bool seats[10][9] = {false};
// int totalTickets=0;
// Ticket ticket[100];


struct Movie{
    string title;
};

struct Studio{
    string number;
};

struct Ticket{
    string movieTitle,time,seat;
    int price;
};

void showTicket(int i,Ticket ticket[]){
    cout<<"Movie : "<<ticket[i].movieTitle<<endl;
    cout<<"seat : "<<ticket[i].seat<<endl;
    cout<<"price : "<<ticket[i].price<<endl;
    // cout<<"Session : "<<ticket[i].time<<endl;
}

void History(int i,int n,Ticket ticket[]){
        if(i==n) {
            return;
        }else{
            showTicket(i,ticket);
            History(i+1,n,ticket);
        }
}

void display(){
    for (int i = 0; i < 10; i++) {
        for(int j=0;j<9;j++){
            cout << "       " << char('A' + i) << j + 1; // Tampilan kursi kosong
        }
        cout << "\n\n";
    }
}
void bookTickets(){
}

int searchHistory(int totalTickets,string seat,string mov,string session,Ticket ticket[],Movie movie[]){
    for(int i=0;i<totalTickets;i++){
        if(seat==ticket[i].seat || session==ticket[i].time) {
            showTicket(i,ticket);
        };
    }

    return 0;
}

int main (){
    int totalTickets=4,totalMovie=10,totalSession=4;
    Ticket ticket[100];
    Movie movie[totalMovie]={"A","B","C","D","E"};
    // Session time[totalSession]={"09.30","12.30","14.00","16.30"};

    // ticket[0].seat="A1";
    // ticket[1].seat="A2";
    // ticket[0].price=15000;
    // ticket[1].price=25000;
    // ticket[2].seat="B1";
    // ticket[3].seat="B2";
    // ticket[2].price=45000;
    // ticket[3].price=35000;
    int i=0;
    char menu='n';
    int choice;

    do{
        system("cls");
        string searchSeat, searchMovie, searchSession;
        cout << "Menu :\n";
        cout << "1. Book for tickets\n";
        cout << "2. Booking History\n";
        cout << "3. Exit \n";
        cout << "Choose for menu : (1/2/3) :";
        cin >> choice;
        
        switch (choice)
        {
        case 1 :
            display();
            bookTickets();
        break;
        case 2: 
            cout<<"Search? (y/n) :";cin>>menu;
            if(menu=='y'){
                cout<<"Input Seat : (A1-J9)";cin>>searchSeat;
                cout<<"Input Movie: :";
                for(int i=0;i<totalMovie;i++){
                    cout<<i+1<<" "<<movie[i].title<<endl;
                }
                ;cin>>searchMovie;
                cout<<"Input Session: ";
                for(int i=0;i<10;i++){
                    cout<<i+1<<" "<<movie[i].title<<endl;
                }
                cin>>searchSession;
                searchHistory(totalTickets,searchSeat,searchMovie,searchSession,ticket,movie);
            }else {
                History(i,totalTickets,ticket);
            }
            system("pause");
        break;

        case 3 :
        cout << "are you sure??? (y/n) : " ; cin >>menu;
        break;
        
        default:
            cout << "error";
        break;
        };

    }while(menu!='y' && menu!='Y');

}


