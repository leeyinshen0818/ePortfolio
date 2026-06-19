#include<iostream>
#include "SimpleCalc.h"
using namespace std;

SimpleCalc::SimpleCalc(double n1, double n2) : num1(n1), num2(n2) {}

double SimpleCalc::add() {
    return num1 + num2;
}

double SimpleCalc::sub() {
    return num1 - num2;
}

double SimpleCalc::mul() {
    return num1 * num2;
}

double SimpleCalc::div() {
    return num1 / num2;
}
