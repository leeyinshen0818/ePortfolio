#include <iostream>
using namespace std;

// Define dataType as int
typedef int dataType;

// Function to perform insertion sort
void insertionSort(dataType data[], int n)
{
    dataType item;
    int pass, insertIndex;
    int comparisons = 0; // Counter for comparisons
    int swaps = 0;       // Counter for swaps

    for (pass = 1; pass < n; pass++)
    {
        item = data[pass];
        insertIndex = pass;

        // Move elements of data[0..pass-1] that are greater than item one position ahead
        while (insertIndex > 0 && data[insertIndex - 1] > item)
        {
            data[insertIndex] = data[insertIndex - 1]; // Shift element up
            insertIndex--;
            swaps++; // Increment swap count
            comparisons++; // Increment comparison count
        }

        // Place the item at its correct position
        data[insertIndex] = item;

        // Increment comparison for the failed while condition check
        if (insertIndex > 0)
            comparisons++;
    } // end for

    // Output the total comparisons and swaps
    cout << "Total Comparisons: " << comparisons << endl;
    cout << "Total Swaps: " << swaps << endl;
}

// Example usage
int main() {
    dataType marks[] = {75, 95, 60, 88, 70};
    int n = sizeof(marks) / sizeof(marks[0]);

    cout << "Original Marks: ";
    for (int i = 0; i < n; i++) {
        cout << marks[i] << " ";
    }
    cout << endl;

    insertionSort(marks, n);

    // Output sorted array
    cout << "Sorted Marks: ";
    for (int i = 0; i < n; i++) {
        cout << marks[i] << " ";
    }
    cout << endl;

    return 0;
}
/*
Item selected = 95, Swap = 0, Comparison = 1
Item selected = 60, Swap = 2, Comparison = 3
Item selected = 88, Swap = 1, Comparison = 2
Item selected = 70, Swap = 3, Comparison = 3
total swap =6, Comparison = 9

Sorted Marks: 60 70 75 88 95
*/