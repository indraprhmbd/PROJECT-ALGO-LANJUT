#include <iostream>
using namespace std;

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
}