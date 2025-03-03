#include <iostream>
using namespace std;

struct Movie{
    string title;
    string producer;
    int release_d;
    int duration;
}; Movie movie[10];

int moviesC;


bool login(){
    string user,pass;
    for(int i=3;i>=0;i--){
        system("cls");
        cout<<"== LOGIN =="<<endl;
        cout<<"Username \t: ";cin>>user;
        cout<<"Password \t: ";cin>>pass;
        system("pause");
        if(user == "admin" && pass == "admin123") return true;
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
        cin  >> movie[i].title;
        cout << "Producer = ";
        cin  >> movie[i].producer;
        cout << "release date = ";
        cin  >> movie[i].release_d;
        cout << "Duration = ";
        cin  >> movie[i].duration;
    }
}

int main(){
    char ulang='t';
    do{ 
        if(login()){
            char menu;
            cout<<"login berhasil!"<<endl;
            system("pause");
            // return 0;
        }else {
            cout<<"Login Failed! Please try again."<<endl;
            system("pause");
        }
        cout<<"Do you want to exit ? (y/n)";cin>>ulang;
        
    }while(ulang!='y');

    int inputmovieC;
    cout << "How many movies you want to input = "; cin >> inputmovieC;
    for(int i = moviesC;  i < inputmovieC + moviesC ; i++){
        cout << "Title = "; 
        cin  >> movie[i].title;
        cout << "Producer = ";
        cin  >> movie[i].producer;
        cout << "release date = ";
        cin  >> movie[i].release_d;
        cout << "Duration = ";
        cin  >> movie[i].duration;
}