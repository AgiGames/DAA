#include <climits>
#include <iostream>
using namespace std;

int find_min(int array[], int n) {

    if (n <= 0) {
        return INT_MIN;
    }

    int min = array[0];
    for (int i = 0; i < n; i++) {
        min = (array[i] < min) ? array[i] : min;
    }

    return min;

}

int find_max(int array[], int n) {

    if (n <= 0) {
        return INT_MIN;
    }

    int max = array[0];
    for (int i = 0; i < n; i++) {
        max = (array[i] > max) ? array[i] : max;
    }

    return max;

}

int main() {

    int array[] = {5, 78, 12, 531, 1325, 7};
    int n =  sizeof(array) / sizeof(array[0]);

    cout << "Minimum Value: " << find_min(array, n) << "\n";
    cout << "Maximum Value: " << find_max(array, n) << "\n";

    return 0;

}
