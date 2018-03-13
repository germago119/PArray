

#include "Sorting.h"

/**
 * QuickSort algorithm
 * @param arr The PagedArray pointer
 * @param left Usually 0, the leftmost index
 * @param right The index number of the rightmost element
 */
void Sorting::quickSort(PagedArray *arr, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr->operator[]((left + right) / 2);

    /* partition */
    while (i <= j) {
        while (arr->operator[](i) < pivot)
            i++;
        while (arr->operator[](j) > pivot)
            j--;
        if (i <= j) {
            tmp = arr->operator[](i);
            arr->operator[](i) = arr->operator[](j);
            arr->operator[](j) = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);

}

/**
 * Selection sort algorithm
 * @param arr The PagedArray pointer to be sorted
 * @param n The number of elements in the array
 */
void Sorting::selectionSort(PagedArray *arr, int n) {
    int i, j, minIndex, tmp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++)
            if (arr->operator[](j) < arr->operator[](minIndex))
                minIndex = j;
        if (minIndex != i) {
            tmp = arr->operator[](i);
            arr->operator[](i) = arr->operator[](minIndex);
            arr->operator[](minIndex) = tmp;
        }
    }
}

/**
 * Insertion sort algorithm
 * @param arr The PagedArray pointer to be sorted
 * @param length The number of elements in the array
 */
void Sorting::insertionSort(PagedArray *arr, int length) {
    int i, j, tmp;
    for (i = 1; i < length; i++) {
        j = i;
        while (j > 0 && arr->operator[](j - 1) > arr->operator[](j)) {
            tmp = arr->operator[](j);
            arr->operator[](j) = arr->operator[](j - 1);
            arr->operator[](j - 1) = tmp;
            j--;
        }
    }
}