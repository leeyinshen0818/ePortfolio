// Convocation ceremony simulation

#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>  // for numeric_limits
#include <cctype>  // for tolower

using namespace std;

class Graduate {
public:
    string name;
    string course;
    double gpa;
    
    // Constructor
    Graduate() : name(""), course(""), gpa(0.0) {}
    
    // Getters
    string getName() const { return name; }
    string getCourse() const { return course; }
    double getGPA() const { return gpa; }
    
    // Setters
    void setName(const string& n) { name = n; }
    void setCourse(const string& c) { course = c; }
    void setGPA(double g) { gpa = g; }
};

class Queue {
private:
    static const int MAX_SIZE = 100;
    Graduate items[MAX_SIZE]; 
    int front;
    int back;
    
public:

    // Constructor
    Queue(){
        front = 0;
        back = -1;
    }
    
    // Destructor
    ~Queue(){}
    
    // To check if the queue is empty
    bool isEmpty() const {
        return back < front;
    }
    
    // To check if the queue is full
    bool isFull() const {
        return back == MAX_SIZE - 1;
    }
    
    // To add a graduate to the queue
    void enQueue(Graduate value) { 
        if (isFull()) {
            throw runtime_error("Queue is full");
        }
        items[++back] = value;
    }
    
    // To remove a graduate from the queue
    void deQueue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        front++;
    }
    
    // To get the first graduate in the queue
    Graduate getFront() const {  
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return items[front];
    }
    
    // To get the last graduate in the queue
    Graduate getRear() const {  
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return items[back];
    }
    
    // To get the size of the queue
    int getSize() const {
        if (isEmpty()) return 0;
        return back - front + 1;
    }
};

class GraduationCeremony {
private:
    vector<Graduate> graduates;  
    Queue graduationQueue; 
    int totalGraduates;
    
    // To display the list of students
    void displayStudentList() {
        cout << "\nRegistered Students:" << endl;
        cout << string(100, '-') << endl;
        cout << setw(5) << "No." 
             << setw(30) << left << "Name"
             << setw(40) << "Course"
             << setw(10) << "GPA" 
             << "Status" << endl;
        cout << string(100, '-') << endl;
        
        if (graduates.empty()) {
            cout << "No students registered yet." << endl;
        } else {
            int count = 1;
            for (const auto& grad : graduates) {
                cout << setw(5) << count++ 
                     << setw(30) << left << grad.getName()
                     << setw(40) << grad.getCourse()
                     << setw(10) << fixed << setprecision(2) << grad.getGPA();
                if (grad.getGPA() >= 3.67) {
                    cout << "Dean's List";
                }
                cout << endl;
            }
        }
        cout << string(100, '-') << endl;
    }
    
public:
    // Constructor
    GraduationCeremony() : totalGraduates(0) {}
    
    // To add a graduate to the list
    void addGraduate() {
        Graduate student;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "\nEnter graduate details" << endl;
        cout << string(30, '-') << endl;
        
        // Name input with validation
        do {
            cout << "Name: ";
            string name;
            getline(cin, name);
            student.setName(name);
            
            if (student.getName().empty()) {
                cout << "Error: Student name cannot be empty!\n";
            }
        } while (student.getName().empty());
        
        // New course selection menu
        cout << "\nSelect Course:" << endl;
        cout << "1 - Data Engineering" << endl;
        cout << "2 - Software Engineering" << endl;
        cout << "3 - Computer Networks & Security" << endl;
        cout << "4 - Graphics and Multimedia Software" << endl;
        
        int courseChoice;
        do {
            cout << "Enter choice (1-4): ";
            cin >> courseChoice;
            
            if (cin.fail() || courseChoice < 1 || courseChoice > 4) {
                cout << "Invalid choice! Please enter a number between 1 and 4\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        } while (true);
        
        // Assign course based on selection
        switch (courseChoice) {
            case 1:
                student.setCourse("Data Engineering");
                break;
            case 2:
                student.setCourse("Software Engineering");
                break;
            case 3:
                student.setCourse("Computer Networks & Security");
                break;
            case 4:
                student.setCourse("Graphics and Multimedia Software");
                break;
        }
        
        do {
            cout << "\nGPA (0.00-4.00): ";
            double gpa;
            cin >> gpa;
            student.setGPA(gpa);
            
            if (cin.fail() || student.getGPA() < 0 || student.getGPA() > 4.0) {
                cout << "Invalid GPA! Please enter a value between 0.00 and 4.00\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        } while (true);
        
        // Add the graduate to the list
        graduates.push_back(student);
        totalGraduates++;
        
        cout << "\nStudent successfully registered!" << endl;
        cout << "Total graduates registered: " << totalGraduates << endl;
        
        // New prompt to add another student
        char addAnother;
        do {
            cout << "\nDo you want to add another student? (Y/N): ";
            cin >> addAnother;
            addAnother = toupper(addAnother);
            
            if (addAnother != 'Y' && addAnother != 'N') {
                cout << "Invalid input! Please enter Y or N" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (addAnother != 'Y' && addAnother != 'N');
        
        if (addAnother == 'Y') {
            addGraduate();  // Recursive call to add another student
        }
    }
    
    // To conduct the graduation ceremony
    void conductCeremony() {
        cout << "\n===Faculty of Computing Graduation Ceremony===" << endl;
        cout << "Total number of graduates: " << totalGraduates << "\n" << endl;
        
        vector<pair<string, int>> waitingArea;  // Now stores name and sequence number
        vector<pair<string, int>> finishArea;   // Now stores name and sequence number
        Queue ceremonyQueue;
        for (const auto& grad : graduates) {
            ceremonyQueue.enQueue(grad);
        }

        // Initial empty waiting area display
        cout << "\nWaiting Area:" << endl;
        cout << string(50, '-') << endl;
        cout << "Empty" << endl;
        cout << string(50, '-') << endl;

        cout << "\n'N' - call the next graduate to arrive" << endl;
        cout << "'F' - view first graduate" << endl;
        cout << "'R' - view last graduate" << endl;
        cout << "\nEnter choice: ";
        string input;
        int sequence = 1;

        // Arrival process
        while (!ceremonyQueue.isEmpty()) {
            getline(cin, input);
            if (input.empty()) continue;  // Handle empty input
            transform(input.begin(), input.end(), input.begin(), ::toupper);
            
            if (input == "F") {
                if (!waitingArea.empty()) {
                    cout << "\nFirst graduate in waiting area: " << waitingArea.front().first 
                         << " (" << waitingArea.front().second << ")" << endl;
                } else {
                    cout << "\nWaiting area is empty." << endl;
                }
                
                // Display current waiting area again
                cout << "\nWaiting Area:" << endl;
                cout << string(50, '-') << endl;
                if (waitingArea.empty()) {
                    cout << "Empty" << endl;
                } else {
                    for (const auto& grad : waitingArea) {
                        cout << grad.first << " (" << grad.second << ")" << endl;
                    }
                }
                cout << string(50, '-') << endl;
                
                cout << "\n'N' - call the next graduate to arrive" << endl;
                cout << "'F' - view first graduate" << endl;
                cout << "'R' - view last graduate" << endl;
                cout << "\nEnter choice: ";
                continue;
            }
            if (input == "R") {
                if (!waitingArea.empty()) {
                    cout << "\nLast graduate in waiting area: " << waitingArea.back().first 
                         << " (" << waitingArea.back().second << ")" << endl;
                } else {
                    cout << "\nWaiting area is empty." << endl;
                }
                
                // Display current waiting area again
                cout << "\nWaiting Area:" << endl;
                cout << string(50, '-') << endl;
                if (waitingArea.empty()) {
                    cout << "Empty" << endl;
                } else {
                    for (const auto& grad : waitingArea) {
                        cout << grad.first << " (" << grad.second << ")" << endl;
                    }
                }
                cout << string(50, '-') << endl;
                
                cout << "\n'N' - call the next graduate to arrive" << endl;
                cout << "'F' - view first graduate" << endl;
                cout << "'R' - view last graduate" << endl;
                cout << "\nEnter choice: ";
                continue;
            }
            if (input != "N") {
                cout << "Invalid input. Please enter 'N', 'F', or 'R'" << endl;
                continue;
            }

            // Move graduate from queue to waiting area
            Graduate current = ceremonyQueue.getFront();
            waitingArea.push_back({current.getName(), sequence++});
            ceremonyQueue.deQueue();

            // Display current waiting area
            cout << "\nWaiting Area:" << endl;
            cout << string(50, '-') << endl;
            for (const auto& grad : waitingArea) {
                cout << grad.first << " (" << grad.second << ")" << endl;
            }
            cout << string(50, '-') << endl;

            if (ceremonyQueue.isEmpty()) {
                cout << "\nAll graduates have arrived!" << endl;
            } else {
                cout << "\n'N' - call the next graduate to arrive" << endl;
                cout << "'F' - view first graduate" << endl;
                cout << "'R' - view last graduate" << endl;
                cout << "\nEnter choice: ";
            }
        }

        // Certificate receiving process
        cout << "\n=== Starting Certificate Ceremony ===" << endl;

        while (!waitingArea.empty()) {
            cout << "\nCurrent Status:" << endl;
            cout << string(80, '-') << endl;
            cout << left << setw(40) << "Waiting Area" << "Finished Area:" << endl;
            cout << string(80, '-') << endl;
            
            // Display both areas side by side
            int maxSize = max(waitingArea.size(), finishArea.size());
            for (size_t i = 0; i < maxSize; i++) {
                if (i < waitingArea.size()) {
                    string gradInfo = waitingArea[i].first + " (" + to_string(waitingArea[i].second) + ")";
                    cout << left << setw(40) << gradInfo;
                } else {
                    cout << setw(40) << "";
                }
                if (i < finishArea.size()) {
                    string gradInfo = finishArea[i].first + " (" + to_string(finishArea[i].second) + ")";
                    cout << gradInfo;
                }
                cout << endl;
            }
            cout << string(80, '-') << endl;

            cout << "\n'N' - call the next graduate to receive cert" << endl;
            cout << "'F' - view first graduate" << endl;
            cout << "'R' - view last graduate" << endl;
            cout << "'Q' - quit" << endl;

            cout << "\nEnter choice: ";
            getline(cin, input);
            transform(input.begin(), input.end(), input.begin(), ::toupper);

            if (input == "Q") {
                cout << "\nCeremony ended early." << endl;
                return;
            }
            if (input == "F" && !waitingArea.empty()) {
                cout << "\nFirst graduate in waiting area: " << waitingArea.front().first 
                     << " (" << waitingArea.front().second << ")" << endl;
                continue;
            }
            if (input == "R" && !waitingArea.empty()) {
                cout << "\nLast graduate in waiting area: " << waitingArea.back().first 
                     << " (" << waitingArea.back().second << ")" << endl;
                continue;
            }
            if (input != "N") continue;

            // Move graduate from waiting to finished area
            auto graduate = waitingArea.front();
            waitingArea.erase(waitingArea.begin());
            finishArea.push_back(graduate);
            
            cout << "\n* " << graduate.first << " (" << graduate.second << ") has received their certificate *" << endl;
        }

        // Show final state with all graduates in finished area
        cout << "\nFinal Status:" << endl;
        cout << string(80, '-') << endl;
        cout << left << setw(40) << "Waiting Area" << "Finished Area:" << endl;
        cout << string(80, '-') << endl;
        for (const auto& grad : finishArea) {
            cout << setw(40) << "" << grad.first << " (" << grad.second << ")" << endl;
        }
        cout << string(80, '-') << endl;

        cout << "\nCeremony finished! Congratulations to all graduates!" << endl;
    }
    
    // To get the total number of graduates
    int getTotalGraduates() const {
        return totalGraduates;
    }
    
    // To display the staff menu
    void staffMenu() {
        while (true) {
            cout << "\n=== Graduation Ceremony System ===" << endl;
            cout << "1. View Student List" << endl;
            cout << "2. Add Student" << endl;
            cout << "3. Start Convocation Ceremony" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            
            int choice;
            while (!(cin >> choice)) {
                cout << "Please enter a correct option (1-4): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            switch (choice) {
                case 1:
                    displayStudentList();
                    break;
                case 2:
                    addGraduate();
                    break;
                case 3:
                    if (getTotalGraduates() > 0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        conductCeremony();
                    } else {
                        cout << "\nNo graduates registered yet." << endl;
                    }
                    break;
                case 4:
                    return;
                default:
                    cout << "Please enter a correct option (1-4)" << endl;
            }
        }
    }
};

int main() {
    // Create an instance of GraduationCeremony
    GraduationCeremony ceremony;
    // Display the staff menu

    ceremony.staffMenu();

    cout << "\nThank you for using the system. Goodbye!" << endl;

    system("pause");
    return 0;
}



