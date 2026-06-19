#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

class Admin {
private:
    string adminID;
    string adminPassword;
    string securityPIN;

public:
    Admin(string adminID, string adminPassword, string securityPIN)
        : adminID(adminID), adminPassword(adminPassword), securityPIN(securityPIN) {}

    static Admin loadAdmin(const string &adminID, const string &adminPassword) {
        ifstream infile("admins.dat");
        string line, id, pass, pin;
        while (getline(infile, line)) {
            istringstream iss(line);
            iss >> id >> pass >> pin;
            if (id == adminID && pass == adminPassword) {
                infile.close();
                return Admin(id, pass, pin);
            }
        }
        infile.close();
        throw runtime_error("Invalid admin credentials.");
    }

    bool authenticate(string pin) {
        return pin == securityPIN;
    }

    void viewUserDetails(const string &userID) {
        ifstream infile("users.dat");
        string line, id, pass, accountNumber, accountType, pin;
        double bal;
        bool userFound = false;

        while (getline(infile, line)) {
            istringstream iss(line);
            iss >> id >> pass >> accountNumber >> accountType >> bal >> pin;
            if (id == userID) {
                cout << "User ID: " << id << "\n";
                cout << "Account Number: " << accountNumber << "\n";
                cout << "Account Type: " << accountType << "\n";
                cout << "Balance: $" << fixed << setprecision(2) << bal << "\n";
                cout << "Security PIN: " << pin << "\n";
                userFound = true;
                break;
            }
        }
        infile.close();

        if (!userFound) {
            cout << "User not found.\n";
        }
    }

    void checkTransactionHistory() {
        ifstream infile("transactions.dat");
        string line;

        cout << "Transaction History:\n";
        cout << "---------------------------------------------------------------------\n";
        cout << "Sender Account | Date       | Time     | Amount  | Recipient Account\n";
        cout << "---------------------------------------------------------------------\n";
        while (getline(infile, line)) {
            istringstream iss(line);
            string senderAcc, date, time, recipientAcc;
            double amount;
            iss >> senderAcc >> date >> time >> amount >> recipientAcc;
            cout << setw(15) << senderAcc << " | "
                 << setw(10) << date << " | "
                 << setw(8) << time << " | "
                 << setw(7) << fixed << setprecision(2) << amount << " | "
                 << setw(17) << recipientAcc << "\n";
        }
        cout << "---------------------------------------------------------------------\n";
        infile.close();
    }
};

#endif
