#include<iostream>
#include<string>
using namespace std ;

const int MAX_SIZE = 100 ;

class Stack{
private:
    char arr[MAX_SIZE] ;
    int top ;

public:
    Stack(){
        top = -1 ;
    }
    
    void push(char x){ 
        if(!isFull()){
            arr[++top] = x ; 
        }
    }

    char pop(){
        return arr[top--] ;
    }

    char stackTop(){
        return arr[top] ; 
    }

    bool isEmpty(){ 
        return top == -1 ; 
    }

    bool isFull(){ 
        return top == MAX_SIZE - 1 ; 
    }

    void display(){
        if (isEmpty()){
            cout << "Stack elements: #" << endl ;
            return;
        }
        
        cout << "Stack elements: #";
        for (int i = 0; i <= top; i++){
            cout << arr[i] ;
        }
        cout << endl ;
    }
};

class Converter{
private:
    string input, output ;
    Stack stack ;
    int position ;

    int precedence(char c){
        if(c == '+' || c == '-') return 1 ;
        if(c == '*' || c == '/') return 2 ;
        if(c == '(') return 0 ;
        return 0;
    }

public:
    Converter(string expr){
        input = expr ;
        position = 0 ;
    }

    void next(){
        if(position >= input.length()){
            while(!stack.isEmpty()) {
                char c = stack.pop() ;
                if(c != '(')
                    output += c ;
            }
        } 
        else{
            char c = input[position] ;
            
            if(isdigit(c)){
                // 15 to 15 instead of 1 5
                while(position < input.length() && isdigit(input[position])) {
                    output += input[position] ;
                    position++ ;
                }
            } 
            else {
                position++ ; // Move position for non-digit characters
                if(isalpha(c)){
                    output += c;
                } 
                else if(c == '('){
                    stack.push(c) ;
                } 
                else if(c == ')'){
                    while(!stack.isEmpty() && stack.stackTop() != '(') {
                        output += stack.pop() ;
                    }
                    if(!stack.isEmpty() && stack.stackTop() == '(') {
                        stack.pop() ;
                    }
                } 
                else{
                    while(!stack.isEmpty() && precedence(c) <= precedence(stack.stackTop())){
                        char topChar = stack.pop() ;
                        if(topChar != '(')
                            output += topChar ;
                    }
                    stack.push(c) ;
                }
            }
        }
        
        cout << "\nInput: " << input << endl ;
        cout << "Current output: " << output << endl ;
        stack.display();
    }

    void displayStack(){
        stack.display() ;
    }

    void displayTop(){
        cout << "Top element: " << stack.stackTop() << endl ; 
    }
};

int main(){
    string expr ;
    char choice ;
 
    cout << "Enter expression: ";
    cin >> expr;

    Converter conv(expr) ;

    while(true){
        cout << "\nN-Next, D-Display, T-Top, Q-Quit: ";
        cin >> choice;

        if(choice == 'N' || choice == 'n') conv.next() ;
        else if(choice == 'D' || choice == 'd') conv.displayStack() ;
        else if(choice == 'T' || choice == 't') conv.displayTop() ;
        else if(choice == 'Q' || choice == 'q') break ;
    }

    return 0;
}