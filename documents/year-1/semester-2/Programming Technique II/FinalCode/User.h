#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class User {
private:
    string userID;
    string password;
    string accountNumber;
    string accountType;
    double balance;
    string securityPIN;
    double withdrawalLimit = 2000.0; // Default withdrawal limit

public:
    User() {}
    User(string userID, string password, string accountNumber, string accountType, double balance, string securityPIN)
        : userID(userID), password(password), accountNumber(accountNumber), accountType(accountType), balance(balance), securityPIN(securityPIN) {}

    void deposit(double amount) {
        balance += amount;
        saveUserData();
    }

    bool withdraw(double amount) {
        if (balance >= amount && amount <= withdrawalLimit) {
            balance -= amount;
            saveUserData();
            return true;
        }
        return false;
    }

    bool transfer(User &receiver, double amount) {
        if (balance >= amount) {
            balance -= amount;
            receiver.deposit(amount);
            saveUserData();
            receiver.saveUserData();

            // Log the transaction
            ofstream outfile("transactions.dat", ios::app);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            outfile << accountNumber << " "
                    << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " "
                    << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << " "
                    << amount << " "
                    << receiver.accountNumber << endl;
            outfile.close();

            return true;
        }
        return false;
    }

    void payBill(double amount) {
        if (balance >= amount) {
            balance -= amount;
            saveUserData();
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void setCreditCardSettings(string newPin) {
        if (!newPin.empty()) {
            securityPIN = newPin;
        }
        cout << "Credit card PIN updated: New PIN: " << securityPIN << endl;
    }

    void setWithdrawalLimit(double newLimit) {
        withdrawalLimit = newLimit;
        cout << "New withdrawal limit: $" << withdrawalLimit << endl;
    }

    static User loadUser(const string &userID, const string &password) {
        ifstream infile("users.dat");
        string line, id, pass, accountNumber, accountType, pin;
        double bal;
        while (getline(infile, line)) {
            istringstream iss(line);
            iss >> id >> pass >> accountNumber >> accountType >> bal >> pin;
            if (id == userID && pass == password) {
                infile.close();
                return User(id, pass, accountNumber, accountType, bal, pin);
            }
        }
        infile.close();
        return User("", "", "", "", 0.0, "");
    }

    static User loadUser(const string &accNum) {
        ifstream infile("users.dat");
        string line, id, pass, accountNumber, accountType, pin;
        double bal;
        while (getline(infile, line)) {
            istringstream iss(line);
            iss >> id >> pass >> accountNumber >> accountType >> bal >> pin;
            if (accountNumber == accNum) {
                infile.close();
                return User(id, pass, accountNumber, accountType, bal, pin);
            }
        }
        infile.close();
        return User("", "", "", "", 0.0, "");
    }

    void saveUserData() {
        ifstream infile("users.dat");
        ofstream outfile("temp.txt");
        string line;

        while (getline(infile, line)) {
            istringstream iss(line);
            string id, pass, accountNumber, accountType, pin;
            double bal;
            iss >> id >> pass >> accountNumber >> accountType >> bal >> pin;

            if (id == userID) {
                outfile << userID << " " << password << " " << accountNumber << " " << accountType << " " << balance << " " << securityPIN << endl;
            } else {
                outfile << line << endl;
            }
        }
        infile.close();
        outfile.close();

        // Remove the original file and rename the temporary file
        remove("users.dat");
        rename("temp.txt", "users.dat");
    }

    bool authenticate(string pin) {
        return pin == securityPIN;
    }

    friend void accountDetails(User &);
    friend void transfer(User &);
    friend void withdraw(User &);
    friend void loginUser();
    friend void payment(User &);
    friend void viewUserAccounts();
};

#endif
