// AHMAD ZIYAAD BIN MOHD ABBAS
// A23CS0206
// IMPROVED BUBBLE SORT
#include <iostream>
using namespace std;

class DataType {
public:
    int x;

    DataType(int value = 0) : x(value) {}

    int getX() {
        return x;
    }
};

// Print the array
void printArray(DataType data[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << data[i].getX() << " ";
    }
    cout << endl;
}

void bubbleSort(DataType data[], int n) { 
    DataType temp;
    bool sorted = false; // false when swaps occur

    for (int pass = 1; (pass < n) && !sorted; ++pass) {
        sorted = true; // assume sorted
        for (int i = 0; i < n - pass; ++i) {
            if (data[i].getX() > data[i + 1].getX()) {
                // Exchange items
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                sorted = false; // signal exchange
            }
        }
        // Print array after each pass
        cout << "Iteration: " << pass << ": ";
        printArray(data, n);
    }
}

int main() {
    DataType d[] = {75, 95, 60, 88, 70};
    int n = sizeof(d) / sizeof(d[0]);

    cout << "Initial array: ";
    printArray(d, n);

    bubbleSort(d, n);

    cout << "Sorted array: ";
    printArray(d, n);

    return 0;
}