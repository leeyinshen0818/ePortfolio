#include <iostream>
using namespace std;

void displayAccountInfo(int);
int deposit( int& , int dps = 500 );
int withdraw(int& , int wtd = 200);

int main(){
    int balance = 200 ;
    char choice ;

    displayAccountInfo(balance) ;
    deposit(balance) ;
    withdraw(balance) ;
    displayAccountInfo(balance) ;

    while(true){
        cout << "\nDo you want to perform another transaction? (Y/N): " ;
        cin >> choice ;

        if(choice == 'Y' || choice == 'y'){
            cout << endl ;
            displayAccountInfo(balance) ;
            deposit(balance) ;
            withdraw(balance) ;
            displayAccountInfo(balance) ;
        }
        else{
            return 0 ;
        }
    }
}

void displayAccountInfo(int balance){
    cout << "<<<<< My Accounts Overview >>>>>" << endl ;
    cout << "Account Holder Name: User 1" << endl ;
    cout << "Account Number: 1013202341" << endl ;
    cout << "Balance: RM " << balance << endl ;
}

int deposit(int &balance, int dps){
    balance += dps ;
    cout << "\n<<<<< Deposit Transaction >>>>>" << endl ;
    cout << "Deposit of RM " << dps << " successful." << endl ;

    return balance ;
}

int withdraw(int &balance, int wtd){
    balance -= wtd ;
    cout << "\n<<<<< Withdrawal Transaction >>>>>" << endl ;
    cout << "Withdrawal of RM " << wtd << " successful. \n" << endl ;

    return balance ;
}