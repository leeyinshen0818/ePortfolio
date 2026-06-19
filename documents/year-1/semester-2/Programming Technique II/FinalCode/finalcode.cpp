#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <conio.h>
#include "User.h"
#include "Admin.h"
using namespace std;

void showMenu() {
    cout << "Main Menu:\n";
    cout << "1. Account Details\n";
    cout << "2. Deposit\n";
    cout << "3. Transfer\n";
    cout << "4. Payment\n";
    cout << "5. Withdraw\n";
    cout << "6. Account Setting\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void waitforUser() {
    cout << "\n\n\nPress any key to go back to main menu...";
    _getch();
    system("cls");
}

void accountDetails(User &user) {
    system("cls");
    cout << "----------------------Account Details--------------------------\n";
    cout << "Equinox Bank Berhad\n\n";
    cout << "== Account Details ==\n\n\n";
    cout << "User ID: " << user.userID << "\n";
    cout << "Account Number: " << user.accountNumber << "\n";
    cout << "Account Type: " << user.accountType << "\n";
    cout << "Balance: $" << fixed << setprecision(2) << user.balance << "\n";
    waitforUser();
}

void deposit(User &user) {
    system("cls");
    cout << "----------------------Deposit--------------------------\n";

    srand(time(0)); // Seed the random number generator with the current time
    int atmSerialNumber = rand() % 10000000000; // Generate a random 10-digit number

    double amount;
    string accountNumber;
    cout << "Enter account to deposit into: ";
    cin >> accountNumber;
    cout << "Enter amount to deposit: $";
    cin >> amount;
    cout << "Please scan the ATM QR code with your device.\n";
    cout << "ATM Serial Number: " << atmSerialNumber << endl; // Display the random ATM serial number
    cout << "Confirm connection (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        cout << "Successful connection.\n";
        cout << "Please insert your money.\n";
        user.deposit(amount);
        cout << "Success!\n";
        cout << "Do you want to print the receipt? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cout << "\nTransaction Date: " << __DATE__ << "\n";
            cout << "Transaction Time: " << __TIME__ << "\n";
            cout << "Account Deposited: " << accountNumber << "\n";
            cout << "Amount Deposited: $" << amount << "\n";

            int intAmount = static_cast<int>(amount);
            int num100 = intAmount / 100;
            intAmount %= 100;
            int num50 = intAmount / 50;
            intAmount %= 50;
            int num20 = intAmount / 20;
            intAmount %= 20;
            int num10 = intAmount / 10;
            intAmount %= 10;
            int num5 = intAmount / 5;
            intAmount %= 5;
            int num1 = intAmount;

            cout << "Denominations: \n";
            cout << "RM100: " << num100 << "\n";
            cout << "RM50: " << num50 << "\n";
            cout << "RM20: " << num20 << "\n";
            cout << "RM10: " << num10 << "\n";
            cout << "RM5: " << num5 << "\n";
            cout << "RM1: " << num1 << "\n";

            waitforUser();
        }
    } else {
        cout << "Connection failed.\n";
    }
}

void transfer(User &user) {
    string ReceiverAccNum, pin;
    double amount;
    
    system("cls");
    cout << "----------------------Transfer--------------------------\n";

ReceiverAccNum:
    cout << "Enter receiver's account number: ";
    cin >> ReceiverAccNum;

    User receiver = User::loadUser(ReceiverAccNum);
    if (receiver.accountNumber.empty()) {
        cout << "Receiver not found.\n";
        goto ReceiverAccNum;
    }

TransferringAmount:
    cout << "Enter amount to transfer (You may transfer up to $ " << fixed << setprecision(2) << user.balance - 10 << "):   $";
    cin >> amount;

    if (user.balance - 10 < amount) {
        cout << "Insufficient balance for transfer.\n";
        goto TransferringAmount;
    }

EnteringPIN:
    cout << "Enter your security PIN: ";
    cin >> pin;

    if (!user.authenticate(pin)) {
        cout << "Security PIN authentication failed.\n";
        goto EnteringPIN;
    }

    if (user.transfer(receiver, amount)) {
        cout << "Transfer successful! " << "\n";
        
        cout << "Do you want to print the receipt? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cout << endl;
            cout << "Date: " << __DATE__ << "\n";
            cout << "Time: " << __TIME__ << "\n";
            cout << "Sender Account Number: " << user.accountNumber << "\n";
            cout << "Recipient Account Number: " << receiver.accountNumber << "\n";
            cout << "Amount Transferred: $" << fixed << setprecision(2) << amount << "\n";
            cout << "New Balance: $" << fixed << setprecision(2) << user.balance << "\n";
        }
    } else {
        cout << "Insufficient balance for transfer.\n";
    }

    waitforUser();
}

void payment(User &user) {
    system("cls");
    cout << "----------------------Payment--------------------------\n";

    double amount;
    string pin;

    cout << "Payment Options:\n";
    cout << "1. Electricity bill\n";
    cout << "2. Water bill\n";
    cout << "3. Telephone bill\n";
    cout << "4. Credit card bill\n";
    cout << "Enter your option: ";
    int option;
    cin >> option;

    string utilityCompany;
    string billType;
    int billNumber;
    double totalBill = rand() % 200;

    switch (option) {
    case 1:
        utilityCompany = "Tenaga Nasional Berhad";
        billType = "Electricity bill";
        billNumber = rand() % 1000000;
        break;
    case 2:
        utilityCompany = "Ranhill Saj";
        billType = "Water bill";
        billNumber = rand() % 1000000;
        break;
    case 3:
        utilityCompany = "CelcomDigi";
        billType = "Telephone bill";
        billNumber = rand() % 1000000;
        break;
    case 4:
        utilityCompany = "Equinox Bank Berhad";
        billType = "Credit card bill";
        billNumber = rand() % 1000000;
        break;
    default:
        cout << "Invalid option.\n";
        return;
    }

    cout << "\nBill number: " << billNumber << "\n";
    cout << "Total bill: RM" << totalBill << "\n";
    cout << "Utility company: " << utilityCompany << "\n";
    cout << "Confirmation (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        cout << "\nPayment successful!\n";
        cout << "Date: " << __DATE__ << "\n";
        cout << "Time: " << __TIME__ << "\n";
        cout << "Account Number: " << user.accountNumber << "\n";
        cout << "Bill Number: " << billNumber << "\n";
        cout << "Amount paid: RM" << totalBill << "\n";
        cout << "Utility company: " << utilityCompany << "\n";
        cout << "Thank you for payment!\n";
        user.payBill(totalBill);
        cout << "New balance: $" << user.balance << "\n";
    } else {
        cout << "Payment cancelled.\n";
    }

    waitforUser();
}

void withdraw(User &user) {
    double amount;
    string pin;
    system("cls");
    cout << "----------------------Withdraw--------------------------\n";

    srand(time(0)); // Seed the random number generator with the current time
    int atmSerialNumber = rand() % 10000000000; // Generate a random 10-digit number

    cout << "Enter amount to withdraw (you may withdraw up to $" << fixed << setprecision(2) << min(user.balance - 10, user.withdrawalLimit) << "):   $";
    cin >> amount;
    if (amount > user.withdrawalLimit) {
        cout << "Amount exceeds the withdrawal limit of $" << user.withdrawalLimit << ".\n";
        return;
    }
    cout << "Please scan the ATM QR code with your device.\n";
    cout << "ATM Serial Number: " << atmSerialNumber << endl; // Display the random ATM serial number
    cout << "Confirm connection (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Connection failed.\n";
        return;
    }

    cout << "Successful connection.\n";
    cout << "Enter your security PIN: ";
    cin >> pin;

    if (!user.authenticate(pin)) {
        cout << "Security PIN authentication failed.\n";
        return;
    }

    if (user.withdraw(amount)) {
        cout << "Withdrawal successful! New balance: $" << user.balance << "\n";
        cout << "Do you want to print the receipt? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cout << "\nWithdrawal Date: " << __DATE__ << "\n";
            cout << "Withdrawal Time: " << __TIME__ << "\n";
            cout << "Account Number: " << user.accountNumber << "\n";
            cout << "Amount Withdrawn: $" << amount << "\n";
            cout << "New Balance: $" << user.balance << "\n";

            int intAmount = static_cast<int>(amount);
            int num100 = intAmount / 100;
            intAmount %= 100;
            int num50 = intAmount / 50;
            intAmount %= 50;
            int num20 = intAmount / 20;
            intAmount %= 20;
            int num10 = intAmount / 10;
            intAmount %= 10;
            int num5 = intAmount / 5;
            intAmount %= 5;
            int num1 = intAmount;

            cout << "Denominations: \n";
            cout << "RM100: " << num100 << "\n";
            cout << "RM50: " << num50 << "\n";
            cout << "RM20: " << num20 << "\n";
            cout << "RM10: " << num10 << "\n";
            cout << "RM5: " << num5 << "\n";
            cout << "RM1: " << num1 << "\n";
        }
    } else {
        cout << "Insufficient balance for withdrawal.\n";
    }

    waitforUser();
}

void accountSetting(User &user) {
    system("cls");
    cout << "----------------------Account Settings--------------------------\n";

    int choice;
    cout << "Choose an option:\n";
    cout << "1. Change Credit Card PIN\n";
    cout << "2. Change Withdrawal Limit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string newPin;
        cout << "Enter new PIN: ";
        cin >> newPin;
        user.setCreditCardSettings(newPin);
    } else if (choice == 2) {
        double newLimit;
        cout << "Enter new withdrawal limit: $";
        cin >> newLimit;
        user.setWithdrawalLimit(newLimit);
    } else {
        cout << "Invalid option.\n";
    }

    waitforUser();
}

void loginUser() {
    string userID, password, pin;

    cout << "Enter User ID: ";
    cin >> userID;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Security PIN: ";
    cin >> pin;

    User user = User::loadUser(userID, password);
    if (user.userID.empty() || !user.authenticate(pin)) {
        cout << "Login failed: Invalid username, password, or security PIN.\n";
        cout << "Wait for 2 seconds to return to the main menu...";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");        
        return;
    }

    cout << "Login successful!\n\n\n";
    for (int i = 3; i > 0; --i) {
        cout << "Redirecting to main menu... " << i << " s" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    system("cls");

    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            accountDetails(user);
            break;
        case 2:
            deposit(user);
            break;
        case 3:
            transfer(user);
            break;
        case 4:
            payment(user);
            break;
        case 5:
            withdraw(user);
            break;
        case 6:
            accountSetting(user);
            break;
        case 7:
            cout << "Exiting...\n\n\n";
            for (int i = 3; i > 0; --i) {
                cout << "Redirecting to login page... " << i << " s" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}

void viewUserAccounts() {
    ifstream file("users.dat");
    if (!file) {
        cout << "\n\nError loading user database...\n";
        return;
    }

    const int MAX_USERS = 20;
    User users[MAX_USERS];
    int numUsers = 0;
    system("cls");
    cout << "----------------------User Accounts--------------------------\n";

    while (numUsers < MAX_USERS && file >> users[numUsers].userID >> users[numUsers].password >> users[numUsers].accountNumber >> users[numUsers].accountType >> users[numUsers].balance >> users[numUsers].securityPIN) {
        numUsers++;
    }

    file.close();

    cout << "User Accounts:\n";
    cout << "---------------------------------------------\n";
    cout << "Account Number      | Account Type | Balance\n";
    cout << "---------------------------------------------\n";
    for (int i = 0; i < numUsers; i++) {
        cout << setw(18) << users[i].accountNumber << " | " << setw(12) << users[i].accountType << " | $" << setw(7) << fixed << setprecision(2) << users[i].balance << "\n";
    }
    cout << "---------------------------------------------\n";

    waitforUser();
}

void loginAdmin() {
    string adminID, password, pin;

    cout << "Enter Admin ID: ";
    cin >> adminID;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Security PIN: ";
    cin >> pin;

    try {
        Admin admin = Admin::loadAdmin(adminID, password);
        if (!admin.authenticate(pin)) {
            throw runtime_error("Invalid security PIN.");
        }

        cout << "Admin login successful!\n\n\n";
        for (int i = 3; i > 0; --i) {
            cout << "Redirecting to main menu... " << i << " s" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        system("cls");

        int choice;
        do {
            cout << "Main Menu:\n";
            cout << "1. View list of users\n";
            cout << "2. View user details\n";
            cout << "3. Check transaction history\n";
            cout << "4. Exit\n";
            cout << "\nEnter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                viewUserAccounts();
                break;
            case 2: {
                string userID;
                cout << "Enter User ID to view details: ";
                cin >> userID;
                admin.viewUserDetails(userID);
                waitforUser();
                break;
            }
            case 3:
                admin.checkTransactionHistory();
                waitforUser();
                break;
            case 4:
                cout << "Exiting...\n\n\n";
                for (int i = 3; i > 0; --i) {
                    cout << "Redirecting to login page... " << i << " s" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    } catch (const runtime_error &e) {
        cout << "Login failed: " << e.what() << "\n";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");
    }
}

int main() {
    int option;
    do {
        cout << "Welcome to Equinox Bank System!\n\n\n";
        cout << "1. Login (User)\n";
        cout << "2. Login (Admin)\n";
        cout << "3. Exit\n\n\n";
        cout << "Enter your choice: ";
        cin >> option;
        switch (option) {
        case 1:
            loginUser();
            break;
        case 2:
            loginAdmin();
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 3);

    return 0;
}
