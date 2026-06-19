// AHMAD ZIYAAD BIN MOHD ABBAS
// A23CS0206
// IMPROVED BUBBLE SORT
#include <iostream>
using namespace std;

void improvedBubbleSort(int arr[], int n, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;
    bool sorted = false;

    for(int pass = 1; pass < n; pass++) {
        sorted = true;
        for (int x = 0; x < n - pass; x++) {
            comparisons++;
            if (arr[x] > arr[x + 1]) {
                int temp = arr[x];
                arr[x] = arr[x + 1];
                arr[x + 1] = temp;
                swaps++;
                sorted = false; // array is not sorted
            }
        }
        if(sorted) break; // array is sorted
    }
}

// pass 1
// 75 95 60 88 70 comparisons++
// 75 60 95 88 70 comparisons++ swap++
// 75 60 88 95 70 comparisons++ swap++
// 75 60 88 70 95 comparisons++ swap++
// comparisons = 4, swaps = 3, array is not sorted

// pass 2
// 60 75 88 70 95 comparisons++ swap++
// 60 75 70 88 95 comparisons++ swap++
// 60 75 70 88 95 comparisons++
// comparisons = 7, swaps = 5, array is not sorted

// pass 3
// 60 75 70 88 95 comparisons++
// 60 70 75 88 95 comparisons++ swap++
// comparisons = 9, swaps = 6, array is not sorted

// pass 4
// 60 70 75 88 95 comparisons++
// comparisons = 10, swaps = 6, array is sorted

int main() {

    int arr[] = {75, 95, 60, 88, 70};
    int n = sizeof(arr) / sizeof(arr[0]); // 20/4 = 5
    int comparisons, swaps;

    improvedBubbleSort(arr, n, comparisons, swaps); 

    cout << "Improved Bubble Sort: " << endl ;
    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) 
        cout << arr[i] << " ";
        cout << "\nComparisons: " << comparisons << "\nSwaps: " << swaps << endl;

    system("pause");
    return 0;
}
