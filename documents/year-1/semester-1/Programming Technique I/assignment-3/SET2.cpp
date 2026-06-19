// LEE YIN SHEN A23CS0236
// NEO LI XIN A23CS0253
#include<iostream>
using namespace std;
const int MAX_OPERATIONS = 100 ;

int multiplyUsingAddition(int, int) ;
void displayMainMenu();
void performMultiplication(int[],int[], int[], int&) ;
void displayResults(int[], int[], int ) ;

int main(){
    int operands1[MAX_OPERATIONS], results[MAX_OPERATIONS] ;
    int choice, operationCount = 0, operandCount[MAX_OPERATIONS] ;

    while(operationCount < MAX_OPERATIONS){
        displayMainMenu() ;
        cout << "Enter your choice: " ;
        cin >> choice ;
        if(choice == 1){
            performMultiplication(operands1, results, operandCount, operationCount) ;
        }
        else if(choice == 2){
            displayResults(results, operandCount, operationCount) ;
        }
        else if(choice == 3){
            cout << "\nGoodbye!" << endl;
            cout << "\n--------------------------------" << endl ;
            break ;
        }
    }
    return 0 ;
}
int multiplyUsingAddition(int a, int b){
    int result = 0 ;
    for(int i = 0 ; i < b ; i++){
        result += a ;
    }
    return result ;
}
void displayMainMenu(){
    cout << "<<<<<Main Menu>>>>>" << endl;
    cout << "=============================" << endl ;
    cout << "1. Perform Multiplication" << endl ;
    cout << "2. Display Results" << endl ;
    cout << "3. Quit" << endl ;
}
void performMultiplication(int operand[], int rst[], int operandC[], int &operationC){
    int resultMultiply = 1, numOperand ;
    cout << "\nEnter the number of operands for multiplication: " ;
    cin >> numOperand ;
    for(int i = 0 ; i < numOperand ; i++){
        cout << "Enter operand " << i + 1 << ": " ;
        cin >> operand[i] ;
        resultMultiply = multiplyUsingAddition(resultMultiply, operand[i]) ;
    }
    rst[operationC] = resultMultiply ;
    operandC[operationC] = numOperand ;
    operationC++ ;
    cout << "\nMultiplication performed successfully!\n" << endl ;
}
void displayResults(int rst[], int numOperand[], int OperationC){
    cout << "\nResults of Mathematical Operations:" << endl ;
    cout << "========================================" << endl ;
    for(int i = 0 ; i < OperationC ; i++){
        cout << "Operation " << i + 1 << ": " << rst[i] << " (Operands: " << numOperand[i] << ")" << endl ;
    }
    cout << endl ;
}

