#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Partition function to rearrange the elements around a pivot
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive function to find the kth smallest element
int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);

        // If pivot itself is the kth smallest element
        if (pivotIndex == k) return arr[pivotIndex];

        // If kth smallest element is in the left subarray
        if (pivotIndex > k) return quickSelect(arr, low, pivotIndex - 1, k);

        // If kth smallest element is in the right subarray
        return quickSelect(arr, pivotIndex + 1, high, k);
    }
    return -1; // Return -1 if k is out of range
}

int main() {
    string filename;
    cout << "Enter the name of the CSV file: ";
    cin >> filename;

   ifstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int n, k;
    file >> n;

    vector<int> arr(n);
    string line;
    getline(file, line); // Read and discard the newline character
    getline(file, line); // Read the line containing elements

    stringstream ss(line);
    for (int i = 0; i < n; ++i) {
        ss >> arr[i];
        char comma; // Discard the comma separator
        ss >> comma;
    }

    cout << "Enter the value of k (1-based index): ";
    cin >> k;

    int result = quickSelect(arr, 0, n - 1, k - 1);
    if (result != -1)
        cout << "The " << k << "th smallest element is: " << result << endl;
    else
        cout << "Invalid input!" << endl;

    return 0;
}

