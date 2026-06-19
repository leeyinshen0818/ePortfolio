// LEE YIN SHEN A23CS0236
// NEO LI XIN A23CS0253
#include<iostream>
#include<string>
using namespace std;
const int MAX_BOOKS = 100 ;

void displayMainMenu() ;
void addBook(string[], string[], int[], int&);
void displayLibrary(string[], string[], int[], int );
void searchBook(string[], string[], int[], int);

int main(){
    string bookTitles[MAX_BOOKS], bookAuthors[MAX_BOOKS] ;
    int bookPublicationYears[MAX_BOOKS], choice, bookCount = 0  ;

    while(bookCount < MAX_BOOKS){
        displayMainMenu() ;
        cout << "Enter your choice: " ;
        cin >> choice ;
        if(choice == 1){
            addBook(bookTitles, bookAuthors, bookPublicationYears, bookCount) ;
        }
        else if(choice == 2){
            displayLibrary(bookTitles, bookAuthors, bookPublicationYears, bookCount) ;
        }
        else if(choice == 3){
            searchBook(bookTitles, bookAuthors, bookPublicationYears, bookCount) ;
        }
        else if(choice == 4){
            cout << "\nGoodbye!" << endl ;
            cout << "\n--------------------------------" << endl ;
            break ;
        }
        else{
            cout << "Enter a valid choice number! " << endl << '\n' ;
        }
    }
    return 0 ;
}
void displayMainMenu(){
    cout << "<<<<<Library Management System>>>>>" << endl ;
    cout << "========================================" << endl ;
    cout << "1. Add a Book" << endl ;
    cout << "2. Display Library" << endl ;
    cout << "3. Search by Title" << endl ;
    cout << "4. Quit" << endl ;
}
void addBook(string bTitles[], string bAuthors[], int bPublicYears[], int &bCount){
    cout << "\nEnter book title: " ;
    cin >> bTitles[bCount] ;
    cout << "Enter author name: " ;
    cin >> bAuthors[bCount] ;
    cout << "Enter publication year: " ;
    cin >> bPublicYears[bCount] ;
    bCount++ ;
    cout << "\nBook added successfully!\n" << endl ;
}
void displayLibrary(string bTitles[], string bAuthors[], int bPublicYears[], int bCount){
    cout << "\nLibrary Contents: " << endl ;
    cout << "====================" << endl ;
    for(int i = 0; i < bCount ; i++){
        cout << "Title: " << bTitles[i] << endl ;
        cout << "Author: " << bAuthors[i] << endl ;
        cout << "Year: " << bPublicYears[i] << endl ;
        cout << '\n' ;
    }
}
void searchBook(string bTitles[], string bAuthors[], int bPulicYears[], int bCount){
    string target ;
    cout << "\nEnter the title to search: " ;
    cin >> target ;
    for(int i = 0 ; i < bCount ; i++){
        if(target == bTitles[i]){
            cout << "\nBook found:" << endl ;
            cout << "====================" << endl ;
            cout << "Title: " << bTitles[i] << endl ;
            cout << "Author: " << bAuthors[i] << endl ;
            cout << "Year: " << bPulicYears[i] << endl ;
            cout << '\n' ;
        }
        else if(target != bTitles[i]){
            cout << "No book found." << endl ;
            cout << '\n' ;
        }
    }
}

