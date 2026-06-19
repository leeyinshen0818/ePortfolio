#include <iostream>
using namespace std;

//{75, 95, 60, 88, 70}
void bubbleSort(int arr[], int n, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;

    for (int pass = 1; pass < n; pass++) { 
        for (int x = 0; x < n - pass; x++) {
            comparisons++;
            if (arr[x] > arr[x + 1]) {
                int temp = arr[x];
                arr[x] = arr[x + 1];
                arr[x + 1] = temp;
                swaps++;
            }
        }
    }
}

// pass 1
// 75 95 60 88 70 comparisons++ 
// 75 60 95 88 70 comparisons++ swap++
// 75 60 88 95 70 comparisons++ swap++
// 75 60 88 70 95 comparisons++ swap++
// comparisons = 4, swaps = 3

// pass 2
// 60 75 88 70 95 comparisons++ swap++
// 60 75 88 70 95 comparisons++ 
// 60 75 70 88 95 comparisons++ swap++
// comparisons = 7, swaps = 5

// pass 3
// 60 75 70 88 95 comparisons++
// 60 70 75 88 95 comparisons++ swap++
// comparisons = 9, swaps = 6

// pass 4
// 60 70 75 88 95 comparisons++
// comparisons = 10, swaps = 6

int main(){
    int arr[] = {75, 95, 60, 88, 70};
    int n = sizeof(arr) / sizeof(arr[0]); //sizeoff(arr) = 20(5 interger, 1 integer = 4 bytes), sizeof(arr[0]) = 4(size of 1 byte)
    int comparisons, swaps;

    bubbleSort(arr, n, comparisons, swaps);

    cout << "Bubble Sort: " << endl ;
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) 
        cout << arr[i] << " ";
        cout << "\nComparisons: " << comparisons << "\nSwaps: " << swaps << endl;

    system("pause");
    return 0;
}
