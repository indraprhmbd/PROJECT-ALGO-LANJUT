#include <iostream>
using namespace std;

bool seats[10][9] = {false};
const int totalTickets=4,totalMovie=10,totalSession=4;
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

string sessions[totalSession]={"10.00","13.00","15.30","18.30"};
Movie movie[totalMovie]={"A","B","C","D","E","F","G","H","I","J"};

void showTicket(int i,Ticket ticket[]){
    cout<<"====================================="<<endl;
    cout<<"Movie \t: "<<ticket[i].movieTitle<<endl; 
    cout<<"seat \t: "<<ticket[i].seat<<endl;
    cout<<"price \t: "<<ticket[i].price<<endl;
    // cout<<"Session : "<<ticket[i].time<<endl;
    // cout<<"====================================="<<endl;
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
int bookTickets(){
    int choices[3];
    cout<<"Choose a movie! : "<<endl;
    for(int i=0;i<totalMovie;i++){
        cout<<i+1<<". "<<movie[i].title<<endl;
    }
    cout<<"choose : ";
    for(int i:choices) return i;
    // return movChoosed[];
}

int searchHistory(int totalTickets,string seat,int mov,int session,Ticket ticket[],Movie movie[]){
    for(int i=0;i<totalTickets;i++){
        if(seat==ticket[i].seat ) {
            showTicket(i,ticket);
            break;
        };
    }

    return 0;
}
string convertions(int mov,int ses,Movie movie[]){
    for(int i=0;i<totalMovie;i++){
        if(mov==i+1) movie[i].title;
    }
    return 0;
}

int main (){
    Ticket ticket[100];
    // Session time[totalSession]={"09.30","12.30","14.00","16.30"};

    ticket[0].seat="A1";
    ticket[1].seat="A2";
    ticket[0].price=15000;
    ticket[1].price=25000;
    ticket[2].seat="B1";
    ticket[3].seat="B2";
    ticket[2].price=45000;
    ticket[3].price=35000;

    int i=0;
    char menu='n';
    int choice;

    do{
        system("cls");
        string searchSeat; int searchMovie, searchSession;
        cout << "Menu :\n";
        cout << "1. Book for tickets\n";
        cout << "2. Booking History\n";
        cout << "3. Exit \n";
        cout << "Choose for menu : (1/2/3) : ";
        cin >> choice;
        switch (choice){
        case 1 :
            bookTickets();
            display();
            system("pause");
        break;
        case 2: 
            cout<<"Search? (y/n) :";cin>>menu;
            if(menu=='y'){
                cout<<"Input Seat (A1-J9)\t: ";cin>>searchSeat;
                for(int i=0;i<totalMovie;i++){
                    cout<<i+1<<". "<<movie[i].title<<endl;
                }
                cout<<"Input Movie \t\t: ";
                cin>>searchMovie;
                for(int i=0;i<totalSession;i++){
                    cout<<i+1<<". "<<sessions[i]<<endl;
                }
                cout<<"Input Session : ";
                cin>>searchSession;
                convertions(searchMovie,searchSession,movie);
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


