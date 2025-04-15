#include <iostream>
using namespace std;

int binary_search(int array[], int n, int target) {

    int low = 0;
    int high = n - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        if (array[mid] == target) {
            return mid;
        }

        if (array[mid] > target) {
            high = mid - 1;
        }

        else {
            low = mid + 1;
        }

    }

    return -1;

}

int main () {

    int array[10] = {1, 5, 67, 89, 90, 101, 200};
    int n = sizeof(array) / sizeof(array[0]);

    int target = 5;

    cout << "Target at index: " << binary_search(array, n, 5) << endl;

    return 0;

}
