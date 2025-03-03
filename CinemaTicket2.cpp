#include <iostream>
using namespace std;

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

int main(){
    char ulang;
    do{ 
        ulang='n';
        bool admin=false;
        if(login(admin)){
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