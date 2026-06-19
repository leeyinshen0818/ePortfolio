#include <iostream>
#include <string>

using namespace std;

// List class definition
class List {
    private:
        Student *head, *last;
        
    public:
        List() { 
            cout << "Create list...\n";
            head = NULL; last = NULL;
        }
        
        void insertNode(Student *newStud) {
        	cout << "Insert " << newStud->getName() << "\n";
        }
        
        Student *findNode(string name) {
            return NULL;
        }
        
        void deleteNode(string name) {
            Student *stud, *prev;
			stud = head;
        }
        
        void displayList() {
        	Student *stud = head;
        	
        	while (stud != NULL) {
        		stud->printResult();
        		stud = stud->getNext();
			}
        }
        
        Student *getHead() { return head; }
        Student *getLast() { return last; }
        
        ~List() {
        	Student *stud = head;
        	cout << "Destroy list...\n";
        	while (stud != NULL) {
        		Student *prevStud = stud;
        		stud = stud->getNext();
        		delete prevStud;
			}
		}
};
