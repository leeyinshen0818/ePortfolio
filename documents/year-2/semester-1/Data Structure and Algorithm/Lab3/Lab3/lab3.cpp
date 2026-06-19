// LEE YIN SHEN
// Score: 10/10
#include <iostream>
#include <string>
using namespace std;

// Define class Node
class Node {
	
    public :
    string name;
    Node* prev;
    Node* next;
    
    Node(string data) {
    	
    	name = data ;
        prev = nullptr ;
        next = nullptr ;
    	
	}
};

// Functions for Doubly Linked List Operations
class DoublyLinkedList {
    Node* head;
    Node* tail;
    
public:
    
	DoublyLinkedList() { 
    
        head = nullptr ;
        tail = nullptr ;
    
	}
    
    // Task 1: Create the list (given)
    void createList() {
        string names[] = {"Ali", "Baba", "Chan", "Diana", "Ely"};
        for (int i = 0; i < 5; i++) {
            insertAtEnd(names[i]);
        }
    }
    
    // Task 1.1 Helper function to insert at the end
    void insertAtEnd(string name) {
        
        Node* newNode1 = new Node(name);

        if (head == nullptr) {
            head = newNode1;
            tail = newNode1;
            return;
        }

        tail->next = newNode1;
        newNode1->prev = tail;
        tail = newNode1;
    }

    // Task 2: Count and display nodes
    void countAndDisplay() {
        
        int count = 0 ;
        Node* temp = head ;
        while(temp != nullptr){
            cout << "Node" << count+1 << ": " << temp->name << endl ;
            count++;
            temp = temp->next;
        }
        cout << "\nTotal nodes: " << count << endl;
        cout << endl ;
    }

    // Task 3: Delete the last node
    void deleteLastNode() {
        
        if(head == nullptr){
            cout << "The list is empty." << endl;
            return;
        }

        if(head->next == nullptr){
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        Node* temp = head;
        while(temp->next->next != nullptr){
            temp = temp->next ;
        }
        delete temp->next ;
        temp->next = nullptr ;
        tail = temp ;

    }

    // Task 4: Insert at the second position
    void insertAtSecond(string name) {
     
        Node* newNode2 = new Node(name);
        
        if (head == nullptr || head->next == nullptr) {
            cout << "The list has less than two nodes." << endl;
            return;
        }

        Node* secondNode = head->next;
        head->next = newNode2;
        newNode2->prev = head;
        newNode2->next = secondNode;
        secondNode->prev = newNode2;
    }

    // Display the list
    void displayList() {
        
        int count = 0 ;
        Node* temp = head ;
        while(temp != nullptr){
            cout << "Node " << count+1 << ": " <<  temp->name << endl ;
            count++;
            temp = temp->next;
        }
        cout << endl ;
    }
};

int main() {
    DoublyLinkedList dll;

    // Task 1: Create the list
    dll.createList();

    // Task 2: Count and display nodes
    dll.countAndDisplay();

    // Task 3: Delete the last node
    dll.deleteLastNode();
    cout << "\nList after deleting last node: " << endl << endl ;
    dll.displayList();

    // Task 4: Insert a node at the second position
    dll.insertAtSecond("Alisa");
    cout << "\nList after inserting 'Alisa' at second position: " << endl << endl ;
    dll.displayList();

    system("pause");
    return 0;
}
