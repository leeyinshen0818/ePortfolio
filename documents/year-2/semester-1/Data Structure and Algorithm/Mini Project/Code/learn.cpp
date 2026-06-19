#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>  // for numeric_limits
#include <cctype>  // for tolower

using namespace std;

struct Graduate {
    string name;
    string degree;
    float gpa;
};

const vector<string> COMPUTING_DEGREES = {
    "Bachelor of Computer Science (Data Engineering) with Honours",
    "Bachelor of Software Engineering with Honours",
    "Bachelor of Computer Science (Computer Networks & Security) with Honours",
    "Bachelor of Computer Science (Graphics and Multimedia Software) with Honours"
};

class GraduationCeremony {
private:
    vector<Graduate> graduates;  // Changed to vector for sorting
    queue<Graduate> graduationLine;
    int totalGraduates;
    
    void displayGraduatesByDegree(const string& degree) {
        cout << "\nGraduates for " << degree << ":" << endl;
        cout << string(50, '-') << endl;
        cout << setw(30) << left << "Name" 
             << setw(10) << "CGPA" << endl;
        cout << string(50, '-') << endl;
        
        // First sort by CGPA within the same degree
        vector<Graduate> degreeGrads;
        for (const auto& grad : graduates) {
            if (grad.degree == degree) {
                degreeGrads.push_back(grad);
            }
        }
        
        sort(degreeGrads.begin(), degreeGrads.end(),
             [](const Graduate& a, const Graduate& b) {
                 return a.gpa > b.gpa;
             });
             
        for (const auto& grad : degreeGrads) {
            cout << setw(30) << left << grad.name 
                 << setw(10) << fixed << setprecision(2) << grad.gpa << endl;
        }
        cout << string(50, '-') << endl;
    }
    
    void displayStudentList(const string& degree) {
        bool found = false;
        cout << "\nStudents in " << degree << ":" << endl;
        cout << string(60, '-') << endl;
        cout << setw(5) << "No." << setw(30) << left << "Name" 
             << setw(10) << "CGPA" << endl;
        cout << string(60, '-') << endl;
        
        int count = 1;
        for (const auto& grad : graduates) {
            if (grad.degree == degree) {
                cout << setw(5) << count++ << setw(30) << left << grad.name 
                     << setw(10) << fixed << setprecision(2) << grad.gpa << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "No students registered for this degree program." << endl;
        }
        cout << string(60, '-') << endl;
    }
    
public:
    GraduationCeremony() : totalGraduates(0) {}
    
    void displayDegreeOptions() {
        cout << "\nFaculty of Computing Degrees:" << endl;
        cout << string(50, '-') << endl;
        for (size_t i = 0; i < COMPUTING_DEGREES.size(); ++i) {
            cout << (i + 1) << ". " << COMPUTING_DEGREES[i] << endl;
        }
        cout << string(50, '-') << endl;
    }
    
    void addGraduate() {
        Graduate student;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "\nEnter graduate details:" << endl;
        cout << "Name: ";
        getline(cin, student.name);
        
        displayDegreeOptions();
        int choice;
        do {
            cout << "Select degree (1-" << COMPUTING_DEGREES.size() << "): ";
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > static_cast<int>(COMPUTING_DEGREES.size())) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice! Please select a number between 1 and " 
                     << COMPUTING_DEGREES.size() << endl;
                continue;
            }
            break;
        } while (true);
        
        student.degree = COMPUTING_DEGREES[choice - 1];
        
        do {
            cout << "CGPA (0.00 - 4.00): ";
            cin >> student.gpa;
            if (cin.fail() || student.gpa < 0 || student.gpa > 4) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid CGPA! Please enter a value between 0 and 4." << endl;
                continue;
            }
            break;
        } while (true);
        
        graduates.push_back(student);
        totalGraduates++;
    }
    
    void sortAndPrepareQueue() {
        // Clear existing queue
        while (!graduationLine.empty()) {
            graduationLine.pop();
        }

        vector<string> selectedOrder;
        vector<bool> selected(COMPUTING_DEGREES.size(), false);

        cout << "\nArrange the order of degree programs for the ceremony:" << endl;
        for (size_t i = 0; i < COMPUTING_DEGREES.size(); ++i) {
            displayDegreeOptions();
            
            int choice;
            do {
                cout << "\nSelect degree program for position " << (i + 1) << ": ";
                cin >> choice;
                if (cin.fail() || choice < 1 || choice > static_cast<int>(COMPUTING_DEGREES.size())) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice! Please select a number between 1 and " 
                         << COMPUTING_DEGREES.size() << endl;
                    continue;
                }
                if (selected[choice - 1]) {
                    cout << "This degree program has already been selected. Please choose another." << endl;
                    continue;
                }
                break;
            } while (true);
            
            selected[choice - 1] = true;
            selectedOrder.push_back(COMPUTING_DEGREES[choice - 1]);
        }

        cout << "\nFinal Ceremony Order:" << endl;
        cout << string(50, '-') << endl;
        
        // Process graduates in the selected degree order
        for (const auto& degree : selectedOrder) {
            displayGraduatesByDegree(degree);
            
            // Add graduates of this degree to the queue (sorted by CGPA)
            vector<Graduate> degreeGrads;
            for (const auto& grad : graduates) {
                if (grad.degree == degree) {
                    degreeGrads.push_back(grad);
                }
            }
            
            sort(degreeGrads.begin(), degreeGrads.end(),
                 [](const Graduate& a, const Graduate& b) {
                     return a.gpa > b.gpa;
                 });
                 
            for (const auto& grad : degreeGrads) {
                graduationLine.push(grad);
            }
        }
    }
    
    void conductCeremony() {
        cout << "\n===Faculty of Computing Graduation Ceremony " << string(20, '=') << endl;
        cout << "Total number of graduates: " << totalGraduates << "\n" << endl;
        
        int count = 0;
        while (!graduationLine.empty()) {
            Graduate student = graduationLine.front();
            count++;
            
            cout << "[Graduate " << count << " of " << totalGraduates << "]\n";
            cout << "Now presenting: " << student.name << endl;
            cout << "Degree: " << student.degree << endl;
            cout << "CGPA: " << fixed << setprecision(2) << student.gpa << endl;
            
            graduationLine.pop();
            cout << "* " << student.name << " has received their cert *\n" << endl;
            
            cout << "Press Enter for next graduate...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "\nCeremony concluded! Congratulations to all graduates!" << endl;
    }
    
    int getTotalGraduates() const {
        return totalGraduates;
    }
    
    void staffMenu() {
        while (true) {
            cout << "\n=== Staff Menu ===" << endl;
            cout << "1. View Student List by Degree" << endl;
            cout << "2. Start Convocation Ceremony" << endl;
            cout << "3. Back to Main Menu" << endl;
            cout << "Enter choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1: {
                    displayDegreeOptions();
                    cout << "Select degree program (1-" << COMPUTING_DEGREES.size() << "): ";
                    int degreeChoice;
                    cin >> degreeChoice;
                    if (degreeChoice >= 1 && degreeChoice <= static_cast<int>(COMPUTING_DEGREES.size())) {
                        displayStudentList(COMPUTING_DEGREES[degreeChoice - 1]);
                    }
                    break;
                }
                case 2:
                    if (getTotalGraduates() > 0) {
                        sortAndPrepareQueue();
                        conductCeremony();
                    } else {
                        cout << "\nNo graduates registered yet." << endl;
                    }
                    break;
                case 3:
                    return;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }

    void studentMenu() {
        while (true) {
            cout << "\n=== Student Menu ===" << endl;
            cout << "1. Add Student Information" << endl;
            cout << "2. Modify Student Information" << endl;
            cout << "3. Back to Main Menu" << endl;
            cout << "Enter choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1: {
                    addGraduate();
                    cout << "\nDo you want to add another student? (y/n): ";
                    char more;
                    cin >> more;
                    if (tolower(more) != 'y') {
                        break;
                    }
                    continue;
                }
                case 2: {
                    modifyStudentInfo();
                    cout << "\nDo you want to modify another student? (y/n): ";
                    char more;
                    cin >> more;
                    if (tolower(more) != 'y') {
                        break;
                    }
                    continue;
                }
                case 3:
                    return;
                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }

    void modifyStudentInfo() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter student name to modify: ";
        string searchName;
        getline(cin, searchName);
        
        for (auto& grad : graduates) {
            if (grad.name == searchName) {
                cout << "\nCurrent Information:" << endl;
                cout << "Name: " << grad.name << endl;
                cout << "Degree: " << grad.degree << endl;
                cout << "CGPA: " << grad.gpa << endl;
                
                cout << "\nEnter new information:" << endl;
                displayDegreeOptions();
                int choice;
                do {
                    cout << "Select new degree (1-" << COMPUTING_DEGREES.size() << "): ";
                    cin >> choice;
                } while (choice < 1 || choice > static_cast<int>(COMPUTING_DEGREES.size()));
                
                grad.degree = COMPUTING_DEGREES[choice - 1];
                
                do {
                    cout << "New CGPA (0.00 - 4.00): ";
                    cin >> grad.gpa;
                } while (grad.gpa < 0 || grad.gpa > 4);
                
                cout << "\nInformation updated successfully!" << endl;
                return;
            }
        }
        cout << "\nStudent not found!" << endl;
    }
};

int main() {
    GraduationCeremony ceremony;
    
    while (true) {
        cout << "\n=== Graduation Ceremony System ===" << endl;
        cout << "1. Staff" << endl;
        cout << "2. Student" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                ceremony.staffMenu();
                break;
            case 2:
                ceremony.studentMenu();
                break;
            case 3:
                cout << "\nThank you for using the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}