#include <iostream>
#include <>//pilih file Ascii.h pada folder klik kanan pilih "Copy Path" kemudian paste pada bagian ini
#include <>//pilih file termcolor.hpp klik kanan  pilih "Copy Path" kemudian paste pada bagian ini
#include <string>
#include <iomanip>
#include <unistd.h> 
#include <stdlib.h> 
#include <ctime>

time_t timestamp;
char timeNow[50];
struct tm * datetime;

using namespace std;
using namespace ascii;

int indeks = 1;
int tiket;
int totalTicket=0;
string nota[90] = {};

string movieArr[100] = {},timeArr[100],seatNum[100];

bool seats[4][4][10][9]={false} ;// Array 4D untuk kursi bioskop dengan 10 baris (A-J) dan 9 kolom


void display(int choiceMov,int choiceTime) {
    cout << "\n\n";
    cout << "\t\t\t\t  " << termcolor::on_yellow <<  "SCREEN THIS SIDE" << termcolor::on_grey << "\n\n";
    cout << termcolor::green <<"  ----------------------------------------------------------------------------------\n\n" << termcolor::white << termcolor::bold;
    
    for (int i = 0; i < 10; i++) {
        for(int j=0;j<9;j++){
            if (seats[choiceMov-1][choiceTime-1][i][j] == false) {
                cout << "       " << termcolor::on_bright_blue << char('A' + i) << j + 1 << termcolor::on_grey; // Tampilan kursi kosong
            } else {
                cout << "       " << termcolor::on_red << char('A' + i) << j + 1 << termcolor::on_grey; // Tampilan kursi kosong
            }
        }
        cout << "\n\n";
    }
    cout << termcolor::green <<"  ----------------------------------------------------------------------------------\n\n" << termcolor::white;
}

void bookTickets(int choiceMov,int choiceTime,string movie, string time, int tiket) {
    string seat;

    int booked = 0;
    for (int i = totalTicket; i < tiket+totalTicket; i++) {
        cout << "Enter row (A-J) and seat number (1-9) for ticket " << i + 1 << ": ";
        cin >> seat;

        nota[i] = seat;
        if(seat[0]>90){
            seat[0] = char(seat[0]-32);
            nota[i][0] = char(nota[i][0]-32);
        }
        int rowIndex = seat[0] - 'A';
        int seatIndex = seat[1] - '1';

        if (rowIndex >= 0 && rowIndex < 10 && seatIndex >= 0 && seatIndex < 9 && seat.length()==2) {
            if (seats[choiceMov-1][choiceTime-1][rowIndex][seatIndex] == false) {
                seats[choiceMov-1][choiceTime-1][rowIndex][seatIndex] = true;
                booked++;
                if(indeks == 99){
                    indeks = 1;
                }
                movieArr[indeks]=movie;
                timeArr[indeks]=time;
                seatNum[indeks]={seat[0],seat[1]};
                indeks++;
                cout <<termcolor::green<< "Seat " <<termcolor::yellow<< seat[0]<<seat[1] <<termcolor::green<< " booked successfully!\n"<<termcolor::white;
            } else {
                cout <<termcolor::red<< "Seat " <<termcolor::yellow<< seat[0]<<seat[1] <<termcolor::red<< " is already booked.\n"<<termcolor::white;
                i--;
            }
        } else {
            cout <<termcolor::red<< "Invalid seat number! Please try again.\n"<<termcolor::white;
            i--;
        }
    }
    totalTicket += tiket;
    cout <<termcolor::green<< "\n" << booked << " ticket(s) booked successfully.\n\n"<<termcolor::white;
}

void cancelBooking(int choiceMov, int choiceTime) {
    string seat;
    cout << "\nEnter row (A-J) and seat number (1-9) to cancel booking: ";
    cin >> seat;
    
    if(seat[0]>90){
            seat[0] = char(seat[0]-32);
        }
        int rowIndex = seat[0] - 'A';
        int seatIndex = seat[1] - '1';

    if (rowIndex >= 0 && rowIndex < 10 && seatIndex >= 0 && seatIndex < 9 && seat.length()==2) {
        for(int i = 0; i<totalTicket; i++){
            if (seats[choiceMov-1][choiceTime-1][rowIndex][seatIndex] == true) {
                if(seat == nota[i]){
                    seats[choiceMov-1][choiceTime-1][rowIndex][seatIndex] = false;
                    for(int j = i; j<totalTicket-1; j++){
                        nota[j] = nota[j+1];
                    }
                    totalTicket--;
                    cout << termcolor::green<<"Booking for seat "<<termcolor::yellow << seat[0]<<seat[1] <<termcolor::green<< " canceled successfully.\n\n"<<termcolor::white;
                } else {
                    cout <<termcolor::red<< "This seat is not booked, so it cannot be canceled.\n\n"<<termcolor::white;               
                    break;
                }
            } else {
                    cout <<termcolor::red<< "This seat is not booked, so it cannot be canceled.\n\n"<<termcolor::white;
                    break;
            }
        }
    } else {
        cout <<termcolor::red<< "Invalid seat number! Please try again.\n"<<termcolor::white;
    }
    cout << endl;    cin.ignore();
    cout << "Press Enter to Continue...";
    cin.get();   
}

string movieName[4] = {"The Shawshank Redemption","Avengers: Endgame","Inception","The Godfather"};
string showTime[4] = {"12.15", "14.20", "16.25", "18.30"};

void movChoice(int &choiceMov,string &movie){
    do{
        cout << endl << termcolor::yellow << setw(88) <<setfill('=')<<"\n";
        cout <<setfill(' ')<< "|  NO |"<< setw(46) <<"Movie Title"<< setw(34) <<"|"<<"\n";
        cout << termcolor::yellow << setw(88) <<setfill('=')<<"\n";
        cout <<setfill(' ')<< "|  1  |" << setw(52) << termcolor::white << movieName[0]<< setw(29) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n";
        cout <<setfill(' ')<< "|  2  |" << setw(48) << termcolor::white << movieName[1]<< setw(33) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n";
        cout <<setfill(' ')<< "|  3  |" << setw(44) << termcolor::white << movieName[2]<< setw(37) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n";
        cout <<setfill(' ')<< "|  4  |" << setw(46) << termcolor::white << movieName[3]<< setw(35) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n"<<termcolor::white;
        cout << "Select Movie (1-4) : "; 
        cin >> choiceMov;
    }while(choiceMov > 4 || choiceMov < 1);   
    movie= movieName[choiceMov-1];
}
void timeChoice(int &choiceTime,string &time){
    do{
        cout << endl;
        cout << endl << termcolor::yellow << setw(88) <<setfill('=')<<"\n";
        cout <<setfill(' ')<< "|  NO |"<< setw(46) <<"Movie Showtime"<< setw(34) <<"|"<<"\n";
        cout << termcolor::yellow << setw(88) <<setfill('=')<<"\n";
        cout <<setfill(' ')<< "|  1  |" << setw(43) << termcolor::white <<showTime[0]<< setw(38) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n";
        cout <<setfill(' ')<< "|  2  |" << setw(43) << termcolor::white <<showTime[1]<< setw(38) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n";
        cout <<setfill(' ')<< "|  3  |" << setw(43) << termcolor::white <<showTime[2]<< setw(38) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n";
        cout <<setfill(' ')<< "|  4  |" << setw(43) << termcolor::white <<showTime[3]<< setw(38) << termcolor::yellow << "|\n" << termcolor::yellow;
        cout << termcolor::yellow << setw(88) <<setfill('-')<<"\n"<<termcolor::white;
        cout << "Select Movie Showtime (1-4) : "; 
        cin >> choiceTime;
    } while(choiceTime > 4 || choiceTime < 1);
    time=showTime[choiceTime-1];
}

void bookHistory(){
    system("cls");
    cout <<"Booking History :"<< endl;
    if(indeks == 1){
        cout << "NONE";
    }
    for(int i = 1; i < indeks; i++){
        cout << i  << ". " << "Movie : " << movieArr[i] << ", Showtime : " <<timeArr[i] << ", Seat : " << seatNum[i] << endl;
    }
    cout << endl << endl;
    cin.ignore();
    cout << "Press Enter to Continue...";
    cin.get();   
}

void printTicket(int choiceMov, int choiceTime){
    int payment;
    time(&timestamp);
    datetime = localtime(&timestamp);
    system("cls");
    cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    cout << endl;
    cout << left << "\t\t\t|" << setfill(' ') << setw(15) << " " << "ITIX" << right << setfill(' ') << setw(17) << "|";
    cout << endl;
    cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    cout << endl;
    strftime(timeNow, 50, "%d %b %Y", datetime);
    cout << "\t\t\t| "<<"Date\t  : " << left << setfill(' ') << setw(24) << timeNow << "|";
    cout << endl;
    strftime(timeNow, 50, "%H:%M", datetime);
    cout << "\t\t\t| "<<"Time\t  : " << left << setfill(' ') << setw(24) << timeNow << "|";
    cout << endl;
    cout << "\t\t\t| "<<"Ticket  : " << left << setfill(' ') << setw(24) << totalTicket << "|";
    cout << endl;
    cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
    cout << endl;
    cout << "\t\t\t| "<<"Total  : Rp " << left << setfill(' ') << setw(22) << 25000*totalTicket << "|";
    cout << endl;
    cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
    cout << endl << endl;
    do{
        cout << "Input Payment : Rp ";cin >> payment;
        if(payment >= totalTicket*25000){
            cout << "Change : Rp " << payment-(totalTicket*25000);
            break;
        } else cout << "Not enough\n";
    } while(true);

    for(int i = 0; i < totalTicket; i++){
        cout << endl;
        cout << termcolor::yellow << "\t\t\t" << right << setfill('=') << setw(38) << " ";
        cout << endl;
        usleep(150000);
        cout << left << "\t\t\t|" << setfill(' ') << setw(15) << " " << termcolor::yellow << "ITIX" << right << setfill(' ') << setw(17) << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t| " << left << setfill(' ') << setw(34) << termcolor::white <<  movieName[choiceMov-1] << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
        cout << endl;
        usleep(150000);
        strftime(timeNow, 50, "%d %b %Y", datetime);
        cout << "\t\t\t| "<< termcolor::white << termcolor::white << "Date\t  : " << left << setfill(' ') << setw(24) << timeNow << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t| "<< termcolor::white << termcolor::white << "Time\t  : " << left << setfill(' ') << setw(24) << showTime[choiceTime-1] << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t| "<< termcolor::white << termcolor::white << "Studio  : " << left << setfill(' ') << setw(24) << choiceMov << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t|" << right << setfill(' ') << setw(36) << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t| "<< termcolor::white << termcolor::white << "Seat\t  : " <<  termcolor::green << nota[i][0] << termcolor::white << "    -    Row  : " << termcolor::green << nota[i][1] << left << setfill(' ') << setw(6) << " " << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t| " << left << setfill(' ') << setw(34) << termcolor::white <<"Rp 25.000" << termcolor::yellow << "|";
        cout << endl;
        usleep(150000);
        cout << "\t\t\t" << right << setfill('=') << setw(38) << " ";    
        usleep(150000);
    }
}
bool login(bool &verify){
    int counter=3;
    while(verify==false && counter>=0){
    string u,p;
    string user[5][2]={ {"arsya","062"},
                        {"bintang","073"},
                        {"biyan","068"},
                        {"ryan","067"},
                        {"jelita","046"}};
    cout<<"\n===================================";
    cout<<"\n|              LOGIN              |";
    cout<<"\n===================================";
    cout<<"\nUsername : "; cin>>u;
    cout<<"Password : "; cin>>p;
    for(int i=0;i<5;i++){
        if(u==user[i][0] && p==user[i][1]){;
        cout<<"Login berhasil!\n";
        verify=true;
        break;
        }
    }
    if(verify==false){

    cout<<"Login salah. Silahkan coba lagi.\n";
    cout<<"Kesempatan tinggal : "<<counter<<endl;
    counter--;
    }
    }
    if(counter==-1){
        cout<<"Kesempatan anda habis.\n";
    }
    return verify;
}

int main() {
    bool verify=false;
    system("cls");
    if(login(verify)){
        system("pause");
        int choice;
        char menu='n';
        int choiceMov=0;
        int choiceTime=0;
        Ascii font = Ascii(block);
        do{
            totalTicket = 0;
            nota[90] = {};
            system("cls");
            cout <<termcolor::blue;
            font.print("ITIX");
            cout <<termcolor::white;
            cout <<setfill(' ')<< endl << setw(54) <<"I F  T I C K E T S\n";
            cout <<setfill(' ')<< setw(45) <<"Powered by "<<termcolor::green<<"Kelompok 3\n"<<termcolor::white;
            
            cout << endl <<"\tMAIN MENU "<< endl;
            cout <<"\t========================"<< endl;
            cout <<"\t1 | Cinema Tickets"<< endl;
            cout <<"\t2 | Booking History"<< endl;
            cout <<"\t3 | Quit"<< endl;
            cout <<"\tChoice : ";cin>>choice;

            if(choice==1){
                system("cls");
                string movie,time;
                movChoice(choiceMov,movie);
                timeChoice(choiceTime,time);
                do {
                    system("cls");
                    display(choiceMov,choiceTime); 
                    cout <<setfill(' ')<<"| "<<choiceMov<<" | "<<movie<< endl;
                    cout <<setfill('-')<< setw(40) <<"\n";    
                    cout <<setfill(' ')<<"| "<<choiceTime<<" | "<<time<< endl;
                    cout << movieArr[0];    
                    cout << "\n\t\t\t\t**** Cinema Tickets *****\n";
                    cout << "\t\t\t\t1. Book tickets\n";
                    cout << "\t\t\t\t2. Cancel Ticket\n";
                    cout << "\t\t\t\t3. Print Ticket\n";
                    cout << "\t\t\t\t4. Back\n";
                    cout << "\t\t\t\tChoice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            cout << "\n\nNumber of tiket to book: ";
                            cin >> tiket;
                            bookTickets(choiceMov,choiceTime,movie,time,tiket);
                            cout << endl << endl;
                            cin.ignore();
                            cout << "Press Enter to Continue...";
                            cin.get();   
                            break;
                        case 2:
                            if(totalTicket == 0){
                                cout << "\nYou havent booked a seat\n";
                                cin.ignore();
                                cout << "Press Enter to Continue...";
                                cin.get();   
                                break;
                            }
                            cancelBooking(choiceMov,choiceTime);
                            break;
                        case 3:
                            if(totalTicket == 0){
                                cout << "\nYou havent booked a seat\n";
                                cin.ignore();
                                cout << "Press Enter to Continue...";
                                cin.get();   
                                break;
                            }
                            printTicket(choiceMov,choiceTime);
                            cout << endl << endl;
                            cin.ignore();
                            cout << termcolor::white << "Press Enter to Continue...";
                            cin.get();   
                            choice = 4;
                            break;
                        case 4: 
                            if(totalTicket > 0){
                                choice = 0;
                                cout << "\nYou Have to print your ticket\n";
                                cin.ignore();
                                cout << "Press Enter to Continue...";
                                cin.get();   
                            }
                            break;
                        default:
                            cout <<termcolor::red<< "Invalid choice. Please try again.\n"<<termcolor::white;
                            break;
                    }
                } while (choice !=4);
            } else if(choice==2){
                bookHistory();
            } else if(choice==3){
                cout <<termcolor::red<<"\nwant to exit? (exit then all data will be deleted)"<<termcolor::white<< endl;
                cout <<"Are you sure you want to quit?(y/n) : ";cin>>menu;
            } else {
                cout <<termcolor::red<< "Invalid choice. Please try again.\n"<<termcolor::white;
            }      
        }while(menu != 'y' && menu != 'Y');
    }
    return 0;
}
