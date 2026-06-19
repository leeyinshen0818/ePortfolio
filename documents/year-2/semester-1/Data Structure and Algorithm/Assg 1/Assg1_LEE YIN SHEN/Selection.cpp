#include <iostream>
using namespace std;

// Function to swap two elements
void swap(int &x, int &y){
    int temp = x;
    x = y;
    y = temp;
}

// Selection Sort function
void selectionSort(int arr[], int n, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;
    for (int last = n - 1; last >= 1; last--){
        int largestIndex = 0; // Assume the first element is the largest
        for (int p = 1; p <= last; p++) {
            comparisons++;
            if (arr[p] > arr[largestIndex]) {
                largestIndex = p;
            }
        }
        // Swap the largest element with the element at the end of the unsorted section
        if (largestIndex != last){
            swap(arr[largestIndex], arr[last]);
            swaps++;
        }
    }
}

// 75 95 60 88 70 - 75 70 60 88 95, comparisons = 4, swaps = 1, largetValue = 95
// 75 70 60 88 95 - 75 70 60 88 95, comparisons = 7, swaps = 1, largetValue = 88
// 75 70 60 88 95 - 60 70 75 88 95, comparisons = 9, swaps = 2, largetValue = 75
// 60 70 75 88 95 - 60 70 75 88 95, comparisons = 10, swaps = 2, largetValue = 70


int main() {
    int arr[] = {75, 95, 60, 88, 70};
    int n = sizeof(arr) / sizeof(arr[0]);
    int comparisons, swaps;

    selectionSort(arr, n, comparisons, swaps);

    cout << "Selection Sort: " << endl ; 
    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) 
        cout << arr[i] << " ";
        cout << "\nComparisons: " << comparisons << "\nSwaps: " << swaps << endl;

    system("pause");
    return 0;
}
