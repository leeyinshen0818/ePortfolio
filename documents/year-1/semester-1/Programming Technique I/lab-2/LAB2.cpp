#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double calculation(int, int, int, int);
void displayTable(int, int, int, int, int, int);
void displayOutput(char, char, double);

int main() {

    int points[][2] = {{1, 3}, {2, 6}, {5, 4}}; // A(1,3) B(2,6) C(5,4)
    char labels[] = {'A', 'B', 'C'};
    double dist;

    displayTable(points[0][0], points[0][1], points[1][0], points[1][1], points[2][0], points[2][1]);

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            dist = calculation(points[i][0], points[i][1], points[j][0], points[j][1]);
            displayOutput(labels[i], labels[j], dist);
        }
    }

    return 0;
}

double calculation(int x1, int y1, int x2, int y2) {
    double dist;
    dist = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    return dist;
}

void displayTable(int x1, int y1, int x2, int y2, int x3, int y3) {
    cout << "A(1,3), B(2,6), and C(5,4)" << endl;
    cout << setw(8) << "x" << setw(7) << "y" << endl;
    cout << left << setw(7) << "A" << x1 << right << setw(7) << y1 << endl;
    cout << left << setw(7) << "B" << x2 << right << setw(7) << y2 << endl;
    cout << left << setw(7) << "C" << x3 << right << setw(7) << y3 << endl;
}

void displayOutput(char p1, char p2, double dist) {
    cout << p1 << p2 << ": " << fixed << setprecision(2) << dist << endl;
}
