#include <iostream>
using namespace std;

bool seats[4][4][10][9] = {false};

struct Session{
    string time;
};

struct Movie{
    string title;
};

struct Studio{
    string number;
};

struct Tiket{
    string seat;
    int price;
    Session time;
    Movie title;
};

void display(){
    for (int i = 0; i < 10; i++) {
        for(int j=0;j<9;j++){
            cout << "       " << char('A' + i) << j + 1; // Tampilan kursi kosong
        }
        cout << "\n\n";
    }
}

int main (){
    char menu='n';
    int choice;
    do{
        cout << "Menu :\n";
        cout << "1. Book for tickets\n";
        cout << "2. Booking History\n";
        cout << "3. Exit \n";
        cout << "Choose for menu : ";
        cin >> choice;
        
        switch (choice)
        {
        case 1 :
            display();
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

