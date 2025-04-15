#include <iostream>
using namespace std;

void merge(int array[], int low, int mid, int high) {

    int temp_array_size = (high - low) + 1;
    int temp_array[temp_array_size] = {0};

    int i = low;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= high) {
        if (array[i] < array[j]) {
            temp_array[k] = array[i];
            i++;
        }
        else {
            temp_array[k] = array[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp_array[k] = array[i];
        i++;
        k++;
    }

    while (j <= high) {
        temp_array[k] = array[j];
        j++;
        k++;
    }

    for (int i = low; i <= high; i++) {
        array[i] = temp_array[i - low];
    }

}

void merge_sort(int array[], int low, int high) {

    if (low == high) {
        return;
    }
    
    int mid = low + (high - low) / 2;
    merge_sort(array, low, mid);
    merge_sort(array, mid + 1, high);
    merge(array, low, mid, high);

}

int main() {

    int array[] = {5, 78, 12, 531, 1325, 7};
    int n =  sizeof(array) / sizeof(array[0]);

    merge_sort(array, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

}
