#include<iostream>
using namespace std;

// Insertion Sort function
void insertionSort(int data[], int n, int &comparisons, int &shifts){

    comparisons = 0;
    shifts = 0;

    int item, insertIndex;

    for (int pass = 1; pass < n; pass++){
        item = data[pass];          // Take the next item to insert
        insertIndex = pass;         // Start at the current index

        // Shift elements to make space for the item
        while ((insertIndex > 0) && (data[insertIndex - 1] > item)) {
            comparisons++;          // Count the comparison
            data[insertIndex] = data[insertIndex - 1];
            insertIndex--;          // Move the index left
            shifts++;               // Count the shift
        }

        // Insert the item at the correct position
        if (insertIndex > 0) {
            comparisons++;          // Account for the last failed comparison
        }
        data[insertIndex] = item;
    }
}

// pass 1
// item = 95, 95 > 75, no shift
// 75 95 60 88 70 
// total comparisons = 1

// pass 2
// item = 60, 60 < 95, shift 95 to the right, shift++
// item = 60, 60 < 75, shift 75 to the right, shift++
// 60 75 95 88 70
// total comparisons = 3, shifts = 2

// pass 3
// item = 88, 88 < 95, shift 95 to the right, shift++
// item = 88, 88 > 75, no shift
// 60 75 88 95 70
// total comparisons = 5, shifts = 3

// pass 4
// item = 70, 70 < 95, shift 95 to the right, shift++
// item = 70, 70 < 88, shift 88 to the right, shift++
// item = 70, 70 < 75, shift 75 to the right, shift++
// item = 70, 70 > 60, no shift
// 60 70 75 88 95
// total comparisons = 9, shifts = 6

int main() {
    int data[] = {75, 95, 60, 88, 70};
    int n = sizeof(data) / sizeof(data[0]);
    int comparisons, shifts;

    insertionSort(data, n, comparisons, shifts);

    cout << "Insertion Sort: " << endl ;
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << "\nComparisons: " << comparisons << "\nShifts: " << shifts << endl;

    system("pause");
    return 0;
}