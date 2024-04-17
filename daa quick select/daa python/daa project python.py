import csv

def partition(arr, low, high):
    pivot = arr[high]  # Choose the last element as the pivot
    i = low - 1  # Index of smaller element

    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def quick_select(arr, low, high, k):
    if low <= high:
        pivot_index = partition(arr, low, high)

        # If pivot itself is the kth smallest element
        if pivot_index == k:
            return arr[pivot_index]

        # If kth smallest element is in the left subarray
        if pivot_index > k:
            return quick_select(arr, low, pivot_index - 1, k)

        # If kth smallest element is in the right subarray
        return quick_select(arr, pivot_index + 1, high, k)

    return -1  # Return -1 if k is out of range


if __name__ == "__main__":
    filename = "input.csv"
    k = int(input("Enter the value of k (1-based index): "))

    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            arr = list(map(int, row))

    result = quick_select(arr, 0, len(arr) - 1, k - 1)
    if result != -1:
        print(f"The {k}th smallest element is: {result}")
    else:
        print("Invalid input!")
