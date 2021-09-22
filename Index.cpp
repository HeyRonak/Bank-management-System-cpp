#include<iostream>
#include<ctime>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Account{
    // string account_type;
    string account_no;
    int balance=500;

    public:
    string getNumber(int n);
    void setBalance();
    int getBalance();
    void transfer_money();
};

class User : public Account{

    string id,password,name,phone,email,address;

    public:
    void register_user();
    void login_user();
    void view_account();
    string generatePassword();

};

int Account::getBalance(){
    return balance;
}



void Account::transfer_money(){
    fstream fin;
    fin.open("users.csv", ios::in);

    fstream fout;
    fout.open("newusers.csv", ios::out);

    string receiver_account_no;
    cout << "Enter your account number:\n";
    getline(cin >> ws , account_no);

    cout << "enter amount that u want to tranfer:\n";
    cin >> balance;

    cout << "Enter receiver account number:\n";
    getline(cin >>ws , receiver_account_no);    

    vector<string> row , updatedAccountSender,updatedAccountReceiver;
    string line, word, temp;

    while (getline(fin , line)) {
        row.clear();
        stringstream s(line);

        while(getline(s, word, ',')) {
            row.push_back(word);
        }


        if(stoi(account_no) == stoi(row[6])){
            updatedAccountSender = row;
        }  
        else if(stoi(receiver_account_no) == stoi(row[6])){
            updatedAccountReceiver = row;
        }else{

            fout << row[0] << ", "
             << row[1] << ", "
             << row[2] << ", "
             << row[3] << ", "
             << row[4] << ", "
             << row[5] << ", "
             << row[6] << ", "
             << row[7]
             << "\n";  

        } 

       
        // int row_size = row.size();

        // if((account_no+",") == row[6]){

        //     cout << "sender found:\n";

        //     stringstream convert;
            
        //     convert << val;  // sending a number as a stream into output string
        //     row[7] = convert.str();

        //     if (!fin.eof()) {
        //         for (int i = 0; i < row_size-1; i++) {
        //             fout << row[i];
        //         }
        //         fout << row[row_size - 1] << "\n";
        //     }

        // }else{

        //      if (!fin.eof()) {
        //         for (int i = 0; i < row_size -1; i++) {
        //             fout << row[i];
        //         }
        //         fout << row[row_size - 1] << "\n";
        //     }

        // }


    }   

    //  simply update data and store in file
    int row_size = updatedAccountSender.size();
    stringstream convert;
    int val =   stoi(updatedAccountSender[7]) - balance;   
    convert << val;  // sending a number as a stream into output string
    updatedAccountSender[7] = convert.str();
    for (int i = 0; i < row_size-1; i++) {
        fout << updatedAccountSender[i] << ", ";
    }
    fout << updatedAccountSender[row_size - 1] << "\n";

    stringstream Receiverconvert;
    int Receiverval =   stoi(updatedAccountReceiver[7]) + balance;   
    Receiverconvert << Receiverval;  // sending a number as a stream into output string
    updatedAccountReceiver[7] = Receiverconvert.str();
    for (int i = 0; i < row_size-1; i++) {
        fout << updatedAccountReceiver[i] << ", ";
    }
    fout << updatedAccountReceiver[row_size - 1] << "\n";

    cout << "\n\nMONEY TRANSFER SUCCESSFULLY :\n\n";
    fout.close();
    fin.close();
    // remove("users.csv");  
    // renaming the updated file with the existing file name
    // rename("newusers.csv", "users.csv");       

}

string Account::getNumber(int n){

    srand(time(0)); // time(0) return no. of second
    char numbers[]  = "123456789";
    string num;
    for(int i=1;i<=n;++i){
       num += numbers[rand() % n+1];
    }
    return num;

}

string User::generatePassword(){

    char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
        'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z' };

    srand(time(0));
    string password;
    for (int i = 1; i <= 10; i++)
        password += letters[rand() % 26];

    return password;
}


void User::register_user(){

    cout << "Enter your Name:\n";
    getline(cin >> ws, name);

    cout << "Enter your phone number:\n";
    getline(cin >> ws, phone);

    cout << "Enter your email:\n";
    getline(cin >> ws, email);

    cout << "Enter your address:\n";
    getline(cin >> ws, address);

    string Account_number = getNumber(8);
    int balance = getBalance();
    id = getNumber(4);
    password = generatePassword();

    //  file handling data storing
    fstream WriteFile;  
    WriteFile.open("users.csv", ios::out | ios::app);

    WriteFile << id << ", "
             << password << ", "
             << name << ", "
             << phone << ", "
             << email << ", "
             << address << ", "
             << Account_number << ", "
             << balance
             << "\n";

    cout << "Register Success:\n";
    WriteFile.close();

}

void User::view_account(){

    fstream fin;
    fin.open("users.csv", ios::in);

    vector<string> row;
    string line, word, temp;

     while (getline(fin, line)){
         row.clear();
         stringstream s(line);

         while(getline(s, word , ',')) {
            row.push_back(word);
         }

        cout << "ID : " << row[0] << "\n";
        cout << "PASSWORD: " << row[1] << "\n";
        cout << "NAME: " << row[2] << "\n";
        cout << "PHONE: " << row[3] << "\n";
        cout << "EMAIL: " << row[4] << "\n";
        cout << "ADDRESS: " << row[5] << "\n";
        cout << "ACCOUNT NO : " << row[6] << "\n";
        cout << "BALANCE: " << row[7] << "\n";

     }

}

int main(){

    User user;
    char ch;
    cout << "\n(1)Login\n";
    cout << "(2)Register\n";
    cout << "(3)Exit\n\n";

    // user.register_user();
    user.view_account();
    // user.transfer_money();

    // cout<<"\n\nWhat is your Choice (1/2/3)\n";
    // cin >> ch;

    // switch(ch){
    //     case '1':
    //         user.login_user();
    //         break;
    //     case '2':
    //         user.register_user();
    //         break;
    //     case '3':
    //         exit(0);
    //         break;
    // }


}