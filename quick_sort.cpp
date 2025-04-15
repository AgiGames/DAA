#include <iostream>
using namespace std;

void swap(int* a, int* b) {

    int temp = *a;
    *a = *b;
    *b = temp;

}

int get_partition(int array[], int low, int high) {

    int pivot = array[high];

    int j = low - 1;

    for (int i = low; i <= high - 1; i++) {
        if (array[i] < pivot) {
            j++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[j + 1], &array[high]);
    return j + 1;

}

void quick_sort(int array[], int low, int high) {

    if (low < high) {

        int partition = get_partition(array, low, high);

        quick_sort(array, low, partition - 1);
        quick_sort(array, partition + 1, high);

    }

}

int main() {

    int array[] = {5, 78, 12, 531, 1325, 7};
    int n =  sizeof(array) / sizeof(array[0]);

    quick_sort(array, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << "\n";

}
