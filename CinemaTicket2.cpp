#include <iostream>
using namespace std;

struct Movie{
    string title;
    string producer;
    string genre;
    string release_d;
    string duration;
}; Movie movie[10];


int moviesC =  0;


string admin[2][1] = {{"admin"}, {"admin123"}};
string cashierUser[4] = {"arsyadi","bintang","biyan","buono"};
string cashierPass[4] = {"062","073","058","090"};

bool cashierCheck(string user,string pass){
    bool u=false,p=false;
    for(int i=0;i<4;i++){
        if(user == cashierUser[i]) u=true;
    }
    for(int i=0;i<4;i++){   
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
        system("pause");
        if(user == "admin" && pass == "admin123") {admin=true;return true;}
        else if(cashierCheck(user,pass)) {
            cout<<"Welcome! "<<user<<" !"<<endl;
            return true;
        }
        cout<<"Username or Password wrong! Try Remaining : "<<i<<endl;
        system("pause");
    }
    return false;
}

void InputMovie(){
    int inputmovieC;
    cout << "How many movies you want to input = "; cin >> inputmovieC;
    for(int i = moviesC;  i < inputmovieC + moviesC ; i++){
        cout << "Title = "; 
        cin.ignore();
        getline(cin,movie[i].title);
        cout << "genre =";
        getline(cin,movie[i].genre);
        cout << "Producer = ";
        getline(cin,movie[i].producer);
        cout << "release date = ";
        getline(cin,movie[i].release_d);
        cout << "Duration = ";
        getline(cin,movie[i].duration);
    }
    int moviesC =+ inputmovieC;
}

void inputschedule(){

}
int main(){
    // char ulang;
    // do{ 
    //     ulang='n';
    //     bool admin=false;
    //     if(login(admin)){
    //         char menu;
    //         cout<<"login berhasil!"<<endl;
    //         system("pause");
    //         // return 0;
    //     }else {
    //         cout<<"Login Failed! Please try again."<<endl;
    //         system("pause");
    //     }
    //     cout<<"Do you want to exit ? (y/n)";cin>>ulang;
        
    // }while(ulang!='y');

    InputMovie();

}