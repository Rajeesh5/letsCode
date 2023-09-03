#include<iostream>
#include<vector>
#include<algorithm>



using namespace std;


int partition(int arr[], int low, int high)
{
    // pivot (Element to be placed at right position)
    int pivot = arr[high];

    int i = low - 1;
     // Index of smaller element and indicates the 
     // right position of pivot found so far

        for (int j = low; j <= high - 1; j++) {

            // If current element is smaller than the pivot
            if (arr[j] < pivot) {
                i++;    // increment index of smaller element
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
}

void quickSort(int arr[], int low, int high) {

    if (low < high) {
        /* pi is partitioning index, arr[pi] is now at right place */
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi

    }
}
void print(int x) {
    cout << x << " ";
}

void print_triplate(int arr[]) {

    // 1. Array is sorted now.
    // 2. Need to find the pair where X+Y+Z = 0 or X+Y = -Z
    // 3. This is very simliter to find the pair where X+Y = Z
    // 4. Now arr[]= {-3,-2,-1,0,1,1,2}



}

int main() {
    int arr[] = { -3, 0, 1, 2, -1, 1, -2 };
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n-1 );


    print_triplate(arr);

    vector<int> vect(arr, arr+n);
    for_each(vect.begin(), vect.end(), print);

    return 0;
}