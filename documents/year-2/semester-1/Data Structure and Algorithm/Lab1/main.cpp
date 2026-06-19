#include<iostream>
#include "SimpleCalc.h"
#include "SimpleCalc.cpp"
using namespace std;

int main() {
    double n1, n2;

    cout << "Enter first number: ";
    cin >> n1;
    cout << "Enter second number: ";
    cin >> n2;

    SimpleCalc calc(n1, n2);

    cout << "The result of addition is: " << calc.add() << endl;
    cout << "The result of subtraction is: " << calc.sub() << endl;
    cout << "The result of the multiplication is: " << calc.mul() << endl;
    cout << "The result of division is: " << calc.div() << endl;

    system("pause") ;
    return 0;
}
