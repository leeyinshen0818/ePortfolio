#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double calculationB(int, int, int = 2, int = 6) ;
double calculationC(int, int, int = 5, int = 4) ;
void displayTable(int, int, int, int, int, int) ;
void displayOutput(char, char, double) ;

int main(){

    int x1 = 1, y1 = 3, x2 = 2, y2 = 6, x3 = 5, y3 = 4 ; //A(1,3) B(2,6) C(5,4)
    char p1 = 'A', p2 = 'B', p3 = 'C' ;
    double dist ;

    displayTable(x1, y1, x2, y2, x3, y3) ;

    for(int x = 0; x <= x3 ; x++){

        if(x == x1){
            dist = calculationB(x1, y1) ;
            displayOutput(p1, p2, dist) ;
            dist = calculationC(x1, y1) ;
            displayOutput(p1, p3, dist) ;
        }

        else if(x == x2){
            dist = calculationC(x2, y2) ;
            displayOutput(p2, p3, dist) ;
        }
    }
    return 0 ;

}

double calculationB(int x1, int y1, int x2 , int y2 ){ //    dist = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)) ;
    double dist ;
    dist = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)) ;

    return dist ;
}

double calculationC(int x1, int y1, int x2 , int y2 ){ //    dist = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)) ;
    double dist ;
    dist = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)) ;

    return dist ;
}

void displayTable(int x1, int y1, int x2, int y2, int x3, int y3){
    cout << "A(1,3), B(2,6), and C(5,4)" << endl ;
    cout << setw(8) << "x" << setw(7) << "y" << endl ;
    cout << left << setw(7) << "A" << x1 << right << setw(7) << y1 << endl ;
    cout << left << setw(7) << "B" << x2 << right << setw(7) << y2 << endl ;
    cout << left << setw(7) << "C" << x3 << right << setw(7) << y3 << endl ;
}

void displayOutput(char p1, char p2, double dist){
    cout << p1 << p2 << ": " << fixed << setprecision(2) << dist << endl ;
}