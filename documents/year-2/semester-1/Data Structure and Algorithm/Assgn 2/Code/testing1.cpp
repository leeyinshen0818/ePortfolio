#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

// Define Node structure for linked list
struct Node {
    char data;
    Node* next;
    Node(char d) : data(d), next(nullptr) {}
};

class Stack {
private:
    Node* top;  // Changed from array to pointer

public:
    Stack() : top(nullptr) {}  // Initialize top pointer to null
    
    void push(char x) { 
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        char value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    char stackTop() {
        return isEmpty() ? '\0' : top->data;
    }

    bool isEmpty() { 
        return top == nullptr;
    }

    // isFull() is no longer needed as linked list can grow dynamically

    void display() {
        if (isEmpty()) {
            cout << "Stack elements: #" << endl;
            return;
        }
        
        cout << "Stack elements: #";
        Node* current = top;
        while (current != nullptr) {
            cout << current->data;
            current = current->next;
        }
        cout << endl;
    }

    // Add destructor to free memory
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class Converter{
private:
    string input;
    string output;
    Stack stack;
    int position;

    int precedence(char c){
        if(c == '+' || c == '-') return 1;
        if(c == '*' || c == '/') return 2;
        if(c == '(') return 0;
        return 0;
    }

public:
    Converter(string expr) : input(expr), position(0) {}

    void next(){
        if(position >= input.length()){
            while(!stack.isEmpty()) {
                char c = stack.pop();
                if(c != '(')
                    output += c;
            }
        } 
        else{
            char c = input[position];
            
            if(isdigit(c)) {
                // Handle multi-digit numbers
                while(position < input.length() && isdigit(input[position])) {
                    output += input[position];
                    position++;
                }
            } 
            else {
                position++; // Move position for non-digit characters
                if(isalpha(c)) {
                    output += c;
                } 
                else if(c == '('){
                    stack.push(c);
                } 
                else if(c == ')'){
                    while(!stack.isEmpty() && stack.stackTop() != '(') {
                        output += stack.pop();
                    }
                    if(!stack.isEmpty() && stack.stackTop() == '(') {
                        stack.pop();
                    }
                } 
                else{
                    while(!stack.isEmpty() && precedence(c) <= precedence(stack.stackTop())){
                        char topChar = stack.pop();
                        if(topChar != '(')
                            output += topChar;
                    }
                    stack.push(c);
                }
            }
        }
        
        cout << "\nInput: " << input << endl;
        cout << "Current output: " << output << endl;
        stack.display();
    }

    void displayStack(){
        stack.display();
    }

    void displayTop(){
        cout << "Top element: " << stack.stackTop() << endl;
    }
};

int main(){
    string expr;
    char choice;

    cout << "Enter expression: ";
    cin >> expr;

    Converter conv(expr) ;

    while(true){
        cout << "\nN-Next, D-Display, T-Top, Q-Quit: ";
        cin >> choice;

        if(choice == 'N' || choice == 'n') conv.next();
        else if(choice == 'D' || choice == 'd') conv.displayStack();
        else if(choice == 'T' || choice == 't') conv.displayTop();
        else if(choice == 'Q' || choice == 'q') break;
    }

    return 0;
}